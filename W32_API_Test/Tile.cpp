#include "Tile.h"



Tile::Tile()
{}

Tile::Tile( const cRectU &Clip, TileType Type )
	:
	type(Type),
	clip(Clip),
	color(type != Passable ? D2D1::ColorF::Black : D2D1::ColorF::Navy )
{
	color.a = type == Passable ? 0.f : 1.f;
}

Tile::Tile( const Tile & Right )
	:
	type( Right.type ),
	clip( Right.clip ),
	color( Right.color )
{}

Tile::Tile( Tile && Right )
	:
	type( Right.type ),
	clip( Right.clip ),
	color( Right.color )
{}

Tile::~Tile()
{}

Tile & Tile::operator=( const Tile & Right )
{
	type = Right.type;
	clip = Right.clip;
	color = Right.color;
	return *this;
}

Tile & Tile::operator=( Tile && Right )
{
	type = Right.type;
	clip = Right.clip;
	color = Right.color;
	return *this;
}

BOOL Tile::IsPassable() const
{
	return type == Passable;
}

BOOL Tile::HasType( TileType Type ) const
{
	BOOL same = type & Type;
	BOOL has_type = same > 0 ? TRUE : FALSE;
	
	return has_type;
}

TileType Tile::GetType() const
{
	return type;
}

cRectU Tile::GetClip() const
{
	return clip;
}

cRectU Tile::GetClipInPixels() const
{
	auto point = Utilities::PointU(
		clip.position.x * clip.size.width,
		clip.position.y * clip.size.height
	);

	return cRectU( point, clip.size );
}

void Tile::Draw( const Camera &Cam, const Graphics & Gfx )const
{
	auto rect = GetClipInPixels();
	auto view = Cam.GetViewRect();

	auto point = Utilities::PointF(
		rect.position.x >= view.position.x ? rect.position.x - view.position.x : 0,
		rect.position.y >= view.position.y ? rect.position.y - view.position.y : 0
	);
	auto size = Utilities::SizeF(
		rect.size.width,
		rect.size.height
	);

	Gfx.DrawFilledRect( Utilities::RectF( point, size), color );
}
