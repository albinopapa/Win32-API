#pragma once
#include "Graphics.h"
#include <Direct2D.h>
#include <string>

class Sprite
{
public:
	Sprite();
	Sprite( const std::wstring &Filename, const Direct2D &D2D );
	~Sprite();

	void Draw( const Utilities::PointT<float> &Position, const Graphics &Gfx );
	void DrawMirrored( const Utilities::PointT<float> &Position, const Graphics &Gfx );
private:
	comptr<ID2D1Bitmap1> bmp;
};

