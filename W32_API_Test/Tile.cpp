#include "Tile.h"



Tile::Tile()
{}

Tile::Tile( const Utilities::RectU & Clip, TileType Type )
	:
	type(Type),
	clip(Clip),
	color(type != Passable ? D2D1::ColorF::Black : D2D1::ColorF::Navy )
{}

Tile::~Tile()
{}

BOOL Tile::IsPassable() const
{
	return type == Passable;
}

TileType Tile::GetType() const
{
	return type;
}

Utilities::RectU Tile::GetClip() const
{
	return clip;
}

Utilities::RectU Tile::GetClipInPixels() const
{
	auto clip = GetClip();
	clip.position.x *= clip.size.width;
	clip.position.y *= clip.size.height;
	return clip;
}

void Tile::Draw( const Camera &Cam, const Graphics & Gfx )
{
	auto rect = GetClipInPixels();
	auto view = Cam.GetViewRect();
	rect = Utilities::RectU( rect.position.x - view.position.x,
		rect.position.y - view.position.y, rect.size.width, rect.size.height );

	Gfx.DrawFilledRect( rect, color );
}
