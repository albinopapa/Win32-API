#pragma once

#include "Window.h"

class AppWindow :
	public Window
{
public:
	AppWindow();
	AppWindow( const std::wstring &Classname, const std::wstring &WinTitle,
		WindowStyle Style = WindowStyle::Overlapped_Window,
		ExtendedWindowStyle ExStyle = ExtendedWindowStyle::Overlapped_Window,
		const Utilities::PointU &Position = {100, 100},
		const Utilities::SizeU &WinSize = {800, 600} );
	~AppWindow();
	operator HWND()const;
	void Create( const std::wstring &Classname, const std::wstring &WinTitle,
		WindowStyle Style = WindowStyle::Overlapped_Window,
		ExtendedWindowStyle ExStyle = ExtendedWindowStyle::Overlapped_Window,
		const Utilities::PointU &Position = {100, 100},
		const Utilities::SizeU &WinSize = {800, 600} )override;
	void RegisterApp( Application *App )override;
	BOOL IsCreated()const;
	Utilities::SizeU Size()const override;
private:
	std::wstring classname, wintitle;
	Utilities::PointU position;
	Utilities::SizeU size;
	HWND hwnd;
	HINSTANCE hInst;
};

