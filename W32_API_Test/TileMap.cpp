#include "TileMap.h"

TileMap::TileMap()
{}

TileMap::TileMap( const std::wstring & MapFilename )
{
	MapLoader load;
	std::wstring map( load( MapFilename ) );

	for( uint32_t i = 0; i < map.size(); ++i )
	{
		Utilities::PointU pos( i % map_width, i / map_width );
		Utilities::SizeU size( tile_size, tile_size );
		Utilities::RectU clip( pos, size );


		switch( map[ i ] )
		{
			case'F':
				tile.push_back( Tile( clip, Floor ) );
				break;
			case'W':
				tile.push_back( Tile( clip, Wall ) );
				break;
			case'C':
				tile.push_back( Tile( clip, Ceiling ) );
				break;
			case'N':
				tile.push_back( Tile( clip, NotPassable ) );
				break;
			default:
				tile.push_back( Tile( clip, Passable ) );
		}
	}
}



TileMap::~TileMap()
{}

Utilities::RectU TileMap::GetWorldBounds() const
{
	Utilities::RectU bounds;
	bounds.size = Utilities::SizeU( map_width * tile_size, map_height * tile_size );
	return std::move( bounds );
}

std::vector<Tile> TileMap::GetClipRects( const Utilities::RectU & Clip ) const
{
	std::vector<Tile> tile_list;
	auto clip = AdjustRect( Clip );

	for( int32_t y = clip.position.y; y <= clip.Bottom(); ++y )
	{
		for( int32_t x = clip.position.x; x <= clip.Right(); ++x )
		{
			Tile t;
			BOOL in_world = GetTile( x, y, t );
			if( !in_world || t.IsPassable() )
				continue;
			tile_list.push_back(std::move(t));
		}
	}

	return std::move( tile_list );
}

void TileMap::Draw( const Camera &Cam, const Graphics & Gfx )
{
	auto view = AdjustRect( Cam.GetViewRect() );
	for( int32_t y = view.position.y; y < view.Bottom(); ++y )
	{
		for( int32_t x = view.position.x; x < view.Right(); ++x )
		{
			Tile t;
			GetTile( x, y, t );
			t.Draw( Cam, Gfx );
		}
	}
}

Utilities::RectU TileMap::AdjustRect( const Utilities::RectU & Clip ) const
{
	Utilities::RectU clip;
	clip.position.x = Clip.position.x / tile_size;
	clip.size.width = Clip.size.width / tile_size;
	clip.position.y = Clip.position.y / tile_size;
	clip.size.height = Clip.size.height / tile_size;

	return std::move( clip );
}

const BOOL TileMap::GetTile( int32_t X, int32_t Y, Tile &T )const
{
	int32_t index = X + ( Y * map_width );
	if( index < 0 )
	{
		return FALSE;
	}

	T = tile[ index ];
}
