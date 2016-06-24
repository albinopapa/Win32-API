#include "Sprite.h"



Sprite::Sprite()
{}

Sprite::Sprite( const std::wstring & Filename, const Direct2D &D2D )
{
	bmp = D2D.CreateBitmap( Filename );
}


Sprite::~Sprite()
{}

void Sprite::Draw( const Utilities::PointT<float> & Position, const Graphics & Gfx )
{	
	Gfx.DrawBitmap( Position, bmp.Get() );
}

void Sprite::DrawMirrored( const Utilities::PointT<float>& Position, const Graphics & Gfx )
{
	Gfx.DrawBitmapMirrored( Position, bmp.Get() );
}
