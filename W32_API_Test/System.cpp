#include "..\Win32 API\Application.h"
#include "..\Win32 API\Application.h"
#include "System.h"

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
	game( gfx, mServ, kServ )
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
		default:
			result = DefWindowProc( win, Message.message, Message.wParam, Message.lParam );
	}

	return result;
}
