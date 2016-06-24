#pragma once

#include <d2d1_2.h>
#include <wincodec.h>
#include <wrl.h>

#pragma comment (lib, "windowscodec.lib")
#pragma comment (lib, "d2d1.lib")

template <class T>
using comptr = Microsoft::WRL::ComPtr<T>;

class Graphics
{
public:
	Graphics();
	~Graphics();

private:
	comptr<ID2D1Device> device;
	comptr<ID2D1DeviceContext> context;

};

