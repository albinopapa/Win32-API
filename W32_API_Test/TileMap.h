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

	cRectU GetWorldBounds()const;
	void Draw( const Camera &Cam, const Graphics &Gfx );

	template<class RectType>
	std::vector<Tile> GetClipRects( const CollisionRect<RectType> &Rect )const
	{
		std::vector<Tile> tile_list;

		auto xStart = static_cast<int32_t>( Rect.Left() ) / tile_size;
		auto xEnd = ( static_cast<int32_t>( Rect.Right() ) ) / tile_size;
		auto yStart = static_cast<int32_t>( Rect.Top() ) / tile_size;
		auto yEnd = ( static_cast<int32_t>( Rect.Bottom() ) ) / tile_size;

		auto _xEndTemp = static_cast<float>( xStart * tile_size );
		auto _yEndTemp = static_cast<float>( yStart * tile_size );

		xEnd = _xEndTemp == Rect.Left() ? xEnd - 1 : xEnd;
		yEnd = _yEndTemp == Rect.Top() ? yEnd - 1 : yEnd;

		for( auto y = yStart; y <= yEnd; ++y )
		{
			for( auto x = xStart; x <= xEnd; ++x )
			{
				Tile t;
				BOOL in_world = GetTile( x, y, t );
				if( !in_world || t.IsPassable() )
					continue;
				tile_list.push_back( std::move( t ) );
			}
		}

		return tile_list;
	}

	template<class RectType>
	BOOL IsUnderCeilingTiles( const CollisionRect<RectType> &Rect )const
	{
		auto xStart = static_cast<int32_t>( Rect.Left() ) / tile_size;
		auto xEnd = ( static_cast<int32_t>( Rect.Right() ) ) / tile_size;
		auto yStart = static_cast<int32_t>( Rect.Top() ) / tile_size;
		auto yEnd = yStart;

		auto _xEndTemp = static_cast<float>( xStart * tile_size );
		auto _yEndTemp = static_cast<float>( yStart * tile_size );

		xEnd = _xEndTemp == Rect.Left() ? xEnd - 1 : xEnd;
		yEnd = _yEndTemp == Rect.Top() ? yEnd - 1 : yEnd;

		BOOL has_ceiling = FALSE;
		for( auto y = yStart; y <= yEnd; ++y )
		{
			for( auto x = xStart; x <= xEnd; ++x )
			{
				Tile t;
				BOOL in_world = GetTile( x, y, t );
				if( !in_world || !t.HasType( Ceiling ) )
					continue;
				has_ceiling = TRUE;
			}
		}

		return has_ceiling;
	}

private:
	cRectU AdjustRect( const cRectU &Clip )const;
	const BOOL GetTile( int32_t X, int32_t Y, Tile &T )const;
private:
	std::vector<Tile> tile;
	Utilities::SizeU size;
	const uint32_t tile_size = 32;
};

