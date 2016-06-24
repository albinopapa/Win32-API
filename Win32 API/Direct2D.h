#pragma once
#include <d2d1_2.h>
#include <wrl.h>
#include <dxgi1_3.h>
#include <d3d11_2.h>

#include "Utilities.h"
#include "AppWindow.h"
#include "WIC.h"

#pragma comment (lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")

class Direct2D
{
public:
	Direct2D(const AppWindow &Win);
	~Direct2D();

	// Resource management
	comptr<ID2D1Bitmap1> CreateBitmap( const std::wstring &Filename )const;
	comptr<ID2D1DrawingStateBlock1> CreateDrawingStateBlock()const;
	comptr<ID2D1SolidColorBrush> CreateSolidColorBrush()const;

	ID2D1DeviceContext *GetContext()const;
	IDXGISwapChain1 *GetSwapchain()const;

private:
	comptr<ID2D1Factory2> factory;
	comptr<ID2D1Device> device;
	comptr<ID2D1DeviceContext> context;
	comptr<ID2D1Bitmap1> render_target;
	comptr<IDXGISwapChain1> swap_chain;
};

