#pragma once
#include <Windows.h>
#include "Application.h"
#include "Utilities.h"

class Window
{
public:
	enum class WindowStyle :uint32_t
	{
		Overlapped_Window = WS_OVERLAPPEDWINDOW,
		Popup = WS_POPUP
	};
	enum class ExtendedWindowStyle :uint32_t
	{
		Overlapped_Window = WS_EX_OVERLAPPEDWINDOW
	};

	Window()
	{}
	virtual void Create( const std::wstring &Classname, const std::wstring &WinTitle,
		WindowStyle Style, ExtendedWindowStyle ExStyle, const Utilities::PointU &Position,
		const Utilities::SizeU &WinSize) = 0;
	virtual void RegisterApp( Application *App ) = 0;
	virtual BOOL IsCreated()const = 0;
	virtual ~Window()
	{}
};

