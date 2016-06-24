#pragma once
#include <wincodec.h>
#include "Utilities.h"
#pragma comment (lib, "windowscodecs.lib")

class WIC
{
public:
	WIC();
	~WIC();

	comptr<IWICBitmap> CreateBitmap(  uint8_t *const Data, const Utilities::SizeT<uint32_t> &Dim );
	comptr<IWICBitmap> CreateBitmap( const Utilities::SizeT<uint32_t> &Dim );
	comptr<IWICBitmap> CreateBitmap( const std::wstring &Filename );
private:
	comptr<IWICImagingFactory2> factory;

};

