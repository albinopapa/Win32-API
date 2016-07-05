#include "..\Win32 API\Application.h"
#include "..\Win32 API\Application.h"
#include "System.h"
#undef max
#undef min

std::unique_ptr<Application> Application::Register()
{
	// TODO: Application or children of Application need move constructor/assignment operator.
	// Can't use std::make_unique I believe because move semantics aren't implemented.
	return std::unique_ptr<System>(new System);
}


System::System()
	:
	win( L"MyClass", L"Test Window" ),
	gfx( win ),
	game( gfx, mouse, kServ )
{
	win.RegisterApp( this );
}


System::~System()
{}

BOOL System::Start()
{
	BOOL result = win.IsCreated();	
	return result;
}

void System::Frame()
{
	game.Go();
}

LRESULT System::MsgProc( const MSG & Message )
{
	LRESULT result = 0;

	switch( Message.message )
	{
		case WM_DESTROY:
			Quit();			
			break;
		case WM_KEYDOWN:
			if( Message.wParam == VK_ESCAPE )
			{
				DestroyWindow( win );
				break;
			}

			kServ.OnKeyPressed( static_cast<uint8_t>( Message.wParam ) );
			break;
		case WM_KEYUP:
			kServ.OnKeyReleased( static_cast<uint8_t>( Message.wParam ) );
			break;
		case WM_MOUSEMOVE:
		{
			auto x = static_cast<int32_t>( Utilities::LoWord( Message.lParam ) );
			auto y = static_cast<int32_t>( Utilities::HiWord( Message.lParam ) );
			auto size = win.Size();

			if( x > 0 && x < size.width && y > 0 && y < size.height )
			{
				mouse.OnMouseMove( x, y );
				if( !mouse.IsInWindow() )
				{
					SetCapture( win );
					mouse.OnMouseEnter();
				}
			}
			else
			{
				if( Message.wParam & ( MK_LBUTTON | MK_RBUTTON ) )
				{
					x = std::max( 0, x );
					x = std::min( int( size.width ) - 1, x );
					y = std::max( 0, y );
					y = std::min( int( size.height ) - 1, y );
					mouse.OnMouseMove( x, y );
				}
				else
				{
					ReleaseCapture();
					mouse.OnMouseLeave();
					mouse.OnLeftReleased( x, y );
					mouse.OnRightReleased( x, y );
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			auto x = static_cast<int32_t>( Utilities::LoWord( Message.lParam ) );
			auto y = static_cast<int32_t>( Utilities::HiWord( Message.lParam ) );
			mouse.OnLeftPressed( x, y );
			break;
		}
		case WM_RBUTTONDOWN:
		{
			auto x = static_cast<int32_t>( Utilities::LoWord( Message.lParam ) );
			auto y = static_cast<int32_t>( Utilities::HiWord( Message.lParam ) );
			mouse.OnRightPressed( x, y );
			break;
		}
		case WM_LBUTTONUP:
		{
			auto x = static_cast<int32_t>( Utilities::LoWord( Message.lParam ) );
			auto y = static_cast<int32_t>( Utilities::HiWord( Message.lParam ) );
			mouse.OnLeftReleased( x, y );
			break;
		}
		case WM_RBUTTONUP:
		{
			auto x = static_cast<int32_t>( Utilities::LoWord( Message.lParam ) );
			auto y = static_cast<int32_t>( Utilities::HiWord( Message.lParam ) );
			mouse.OnRightReleased( x, y );
			break;
		}
		case WM_MOUSEWHEEL:
		{
			auto x = static_cast<int32_t>( Utilities::LoWord( Message.lParam ) );
			auto y = static_cast<int32_t>( Utilities::HiWord( Message.lParam ) );
			if( GET_WHEEL_DELTA_WPARAM( Message.wParam ) > 0 )
			{
				mouse.OnWheelUp( x, y );
			}
			else if( GET_WHEEL_DELTA_WPARAM( Message.wParam ) < 0 )
			{
				mouse.OnWheelDown( x, y );
			}
			break;
		}
		default:
			result = DefWindowProc( win, Message.message, Message.wParam, Message.lParam );
	}

	return result;
}
