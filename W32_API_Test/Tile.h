#pragma once
#include "Graphics.h"
#include "Camera.h"

enum TileType
{
	Passable	= 0x000, 
	Ceiling		= 0b001,
	Wall		= 0b010,
	Floor		= 0b100,
	NotPassable = Floor | Wall | Ceiling
};

class Tile
{
public:
	Tile();
	Tile(const cRectU &Clip, TileType Type);
	Tile( const Tile &Right );
	Tile( Tile&& Right );
	~Tile();

	Tile &operator=( const Tile &Right );
	Tile &operator=( Tile &&Right );

	BOOL IsPassable()const;
	BOOL HasType( TileType Type )const;

	TileType GetType()const;

	cRectU GetClip()const;
	cRectU GetClipInPixels()const;
	void Draw( const Camera &Cam, const Graphics &Gfx )const;
private:
	TileType type;
	cRectU clip;
	D2D1::ColorF color = D2D1::ColorF(D2D1::ColorF::Black, 0.f);
};

