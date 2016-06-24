#include "WIC.h"



WIC::WIC()
{
	CoInitialize( nullptr );
	CoCreateInstance(
		CLSID_WICImagingFactory1,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS( factory.GetAddressOf() )
	);
}


WIC::~WIC()
{
	CoUninitialize();
}

comptr<IWICBitmap> WIC::CreateBitmap( uint8_t *const Data, const Utilities::SizeT<uint32_t> &Dim )
{
	comptr<IWICBitmap> bitmap;
	HRESULT hr = factory->CreateBitmap( Dim.width, Dim.height,
		GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnDemand,
		bitmap.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	WICRect r{};
	r.Width = Dim.width;
	r.Height = Dim.height;

	uint32_t stride = Dim.width * 4;
	uint32_t buffer_size = stride * Dim.height;
	
	hr = bitmap->CopyPixels( &r, stride, buffer_size, Data );
	assert( SUCCEEDED( hr ) );

	return std::move(bitmap);
}

comptr<IWICBitmap> WIC::CreateBitmap( const Utilities::SizeT<uint32_t> & Dim )
{
	comptr<IWICBitmap> bitmap;
	HRESULT hr = factory->CreateBitmap( Dim.width, Dim.height,
		GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnDemand,
		bitmap.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	return std::move( bitmap );
}

comptr<IWICBitmap> WIC::CreateBitmap( const std::wstring & Filename )
{
	comptr<IWICBitmapDecoder> decoder;
	comptr<IWICBitmapFrameDecode> frame;
	comptr<IWICFormatConverter> converter;
	comptr<IWICBitmap> bitmap;
	HRESULT hr = S_OK;

	hr = factory->CreateDecoderFromFilename( Filename.c_str(), nullptr,
		GENERIC_READ, WICDecodeMetadataCacheOnDemand, decoder.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	hr = decoder->GetFrame( 0, frame.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	hr = factory->CreateFormatConverter( converter.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	hr = converter->Initialize( frame.Get(), GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeCustom );
	assert( SUCCEEDED( hr ) );

	hr = factory->CreateBitmapFromSource( converter.Get(), WICBitmapCacheOnDemand,
		bitmap.GetAddressOf() );
	assert( SUCCEEDED( hr ) );

	return std::move(bitmap);
}
