#include "AppWindow.h"



AppWindow::AppWindow()
{}

AppWindow::AppWindow( const std::wstring & Classname, const std::wstring & WinTitle,
	WindowStyle Style, ExtendedWindowStyle ExStyle,
	const Utilities::PointU & Position, const Utilities::SizeU & WinSize )
{
	Create( Classname, WinTitle, Style, ExStyle, Position, WinSize );
}

AppWindow::operator HWND()const
{
	return hwnd;
}

void AppWindow::Create( const std::wstring & Classname, const std::wstring & WinTitle, 
	WindowStyle Style, ExtendedWindowStyle ExStyle, 
	const Utilities::PointU & Position, const Utilities::SizeU & WinSize )
{
	classname = Classname;
	wintitle = WinTitle;
	position = Position;
	size = WinSize;
	hInst = GetModuleHandle( nullptr );

	WNDCLASSEX wc{};
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.hInstance = hInst;
	wc.lpfnWndProc = MsgProc;
	wc.lpszClassName = classname.c_str();

	RegisterClassEx( &wc );

	uint32_t ex_style = static_cast<uint32_t>( ExStyle );
	uint32_t style = static_cast<uint32_t>( Style );
	
	hwnd = CreateWindowEx( ex_style, Classname.c_str(), WinTitle.c_str(),
		style, Position.x, Position.y, WinSize.width, WinSize.height, 
		nullptr, nullptr, hInst, nullptr );

	ShowWindow( hwnd, SW_SHOWDEFAULT );
}

void AppWindow::RegisterApp( Application * App )
{
	SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>( App ) );
}

BOOL AppWindow::IsCreated() const
{
	return hwnd != nullptr;
}

Utilities::SizeU AppWindow::Size() const
{
	return size;
}

AppWindow::~AppWindow()
{
	UnregisterClass( classname.c_str(), hInst );
}
