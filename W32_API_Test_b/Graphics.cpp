#include "Graphics.h"
#include <d3d11_2.h>
#include <assert.h>
#pragma comment (lib, "d3d11.lib")

Graphics::Graphics()
{
	comptr<IDXGIDevice> dxgi_device;
	comptr<ID3D11Device> d3d_device;

	HRESULT hr = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		nullptr, 0, D3D11_SDK_VERSION, d3d_device.GetAddressOf(), nullptr, nullptr );
	assert( SUCCEEDED( hr ) );

	hr = d3d_device.As( &dxgi_device );
	assert( SUCCEEDED( hr ) );

	hr = D2D1CreateDevice( dxgi_device.Get(), D2D1_CREATION_PROPERTIES{}, device.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	hr = device->CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS{}, context.GetAddressOf() );
	assert( SUCCEEDED( hr ) );
}


Graphics::~Graphics()
{}
