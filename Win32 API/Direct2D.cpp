#include "Direct2D.h"
#include "WIC.h"
#include <d3d11_2.h>

Direct2D::Direct2D( const AppWindow &Win )
{
	comptr<IDXGIDevice> dxgi_device;
	comptr<ID3D11Device> d3d_device;
	comptr<IDXGIAdapter> adapter;
	comptr<IDXGIFactory2> dxgi_factory;

	HRESULT hr = D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, factory.GetAddressOf() );
	assert( SUCCEEDED( hr ) );
	
	hr = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		nullptr, 0, D3D11_SDK_VERSION, d3d_device.GetAddressOf(), nullptr, nullptr );
	assert( SUCCEEDED( hr ) );

	hr = d3d_device.As( &dxgi_device );
	assert( SUCCEEDED( hr ) );

	hr = factory->CreateDevice( dxgi_device.Get(), device.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	hr = device->CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS{}, context.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	hr = dxgi_device->GetAdapter( adapter.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	hr = adapter->GetParent( IID_PPV_ARGS( dxgi_factory.GetAddressOf() ) );
	assert( SUCCEEDED( hr ) );

	DXGI_SWAP_CHAIN_DESC1 scd{};
	scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.SampleDesc = {1,0};
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 2;
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	
	hr = dxgi_factory->CreateSwapChainForHwnd( 
		dxgi_device.Get(), Win, &scd, nullptr, nullptr, swap_chain.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	comptr<IDXGISurface> back_buffer;
	hr = swap_chain->GetBuffer( 0, IID_PPV_ARGS( back_buffer.GetAddressOf() ) );
	assert( SUCCEEDED( hr ) );

	D2D1_PIXEL_FORMAT pix_format =
		D2D1::PixelFormat( DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED );
	
	D2D1_BITMAP_OPTIONS options = 
		D2D1_BITMAP_OPTIONS_CANNOT_DRAW | D2D1_BITMAP_OPTIONS_TARGET;

	D2D1_BITMAP_PROPERTIES1 bmp_props = D2D1::BitmapProperties1( options, pix_format );		

	hr = context->CreateBitmapFromDxgiSurface( 
		back_buffer.Get(), bmp_props, render_target.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	context->SetTarget( render_target.Get() );
}

Direct2D::~Direct2D()
{}

comptr<ID2D1Bitmap1> Direct2D::CreateBitmap( const std::wstring &Filename )const
{
	HRESULT hr = S_OK;
	comptr<ID2D1Bitmap1> bitmap;
	WIC wic;

	hr = context->CreateBitmapFromWicBitmap( 
		wic.CreateBitmap( Filename ).Get(), 
		bitmap.GetAddressOf() 
	);
	assert( SUCCEEDED( hr ) );

	return bitmap;
}

comptr<ID2D1DrawingStateBlock1> Direct2D::CreateDrawingStateBlock() const
{
	comptr<ID2D1DrawingStateBlock1> pState;
	factory->CreateDrawingStateBlock( pState.GetAddressOf() );
	return std::move( pState );
}

comptr<ID2D1SolidColorBrush> Direct2D::CreateSolidColorBrush()const
{
	comptr<ID2D1SolidColorBrush> brush;
	context->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::Black ), brush.GetAddressOf() );
	return std::move( brush );
}

comptr<ID2D1LinearGradientBrush> Direct2D::CreateLinearGradientBrush(
	ID2D1GradientStopCollection *pStopCollection, 
	const Utilities::RectF &BrushRect )
{
	comptr<ID2D1LinearGradientBrush> lingrad_brush;
	D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES props{};
	props.startPoint = D2D1::Point2F( BrushRect.Left(), BrushRect.Top() );
	props.endPoint = D2D1::Point2F( BrushRect.Right(), BrushRect.Bottom() );
	context->CreateLinearGradientBrush( props, pStopCollection, lingrad_brush.GetAddressOf() );

	return lingrad_brush;
}

comptr<ID2D1GradientStopCollection> Direct2D::CreateGradientStopCollection(
	const std::vector<D2D1_GRADIENT_STOP> &Stops )
{
	comptr<ID2D1GradientStopCollection> pStopCollection;
	context->CreateGradientStopCollection( Stops.data(), Stops.size(),
		pStopCollection.GetAddressOf() );

	return pStopCollection;
}

ID2D1DeviceContext *Direct2D::GetContext() const
{
	return context.Get();
}

IDXGISwapChain1 * Direct2D::GetSwapchain() const
{
	return swap_chain.Get();
}

