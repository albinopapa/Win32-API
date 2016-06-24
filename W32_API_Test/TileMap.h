#pragma once

#include <vector>
#include "Tile.h"
#include "MapLoader.h"
#include "Camera.h"

class TileMap
{
public:
	TileMap();
	TileMap( const std::wstring &MapFilename);
	~TileMap();

	Utilities::RectU GetWorldBounds()const;
	std::vector<Tile> GetClipRects(const Utilities::RectU &Clip)const;
	void Draw( const Camera &Cam, const Graphics &Gfx );
private:
	Utilities::RectU AdjustRect( const Utilities::RectU &Clip )const;
	const BOOL GetTile( int32_t X, int32_t Y, Tile &T )const;
private:
	std::vector<Tile> tile;
	const uint32_t map_width = 100;
	const uint32_t map_height = 18;
	const uint32_t tile_size = 32;
};

