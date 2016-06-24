#pragma once
#include <Utilities.h>
#include "Graphics.h"
#include "Camera.h"

enum TileType
{
	Passable, Floor, Wall, Ceiling, NotPassable
};

class Tile
{
public:
	Tile();
	Tile(const Utilities::RectU &Clip, TileType Type);
	~Tile();

	BOOL IsPassable()const;
	TileType GetType()const;

	Utilities::RectU GetClip()const;
	Utilities::RectU GetClipInPixels()const;
	void Draw( const Camera &Cam, const Graphics &Gfx );
private:
	TileType type;
	Utilities::RectU clip;
	D2D1::ColorF color = D2D1::ColorF(D2D1::ColorF::Navy);
};

