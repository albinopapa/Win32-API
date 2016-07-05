#include "TileMap.h"

TileMap::TileMap()
{}

TileMap::TileMap( const std::wstring & MapFilename )
{
	MapLoader load;
	std::wstring map( load( MapFilename ) );
	size = load.Size();
	Utilities::SizeU t_size( tile_size, tile_size );

	Utilities::PointU pos;
	for( uint32_t y = 0; y < size.height; ++y )
	{
		pos.y = y;
		uint32_t y_offset = y * size.width;
		for( uint32_t x = 0; x < size.width; ++x )
		{
			pos.x = x;
			cRectU clip( pos, t_size );

			switch( map[ x + y_offset ] )
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
}



TileMap::~TileMap()
{}

cRectU TileMap::GetWorldBounds() const
{
	cRectU bounds;
	bounds.size.width = size.width * tile_size;
	bounds.size.height = size.height * tile_size;
	return bounds;
}

void TileMap::Draw( const Camera &Cam, const Graphics & Gfx )
{
	auto screen = AdjustRect( Cam.GetViewRect() );

	auto xStart = screen.Left();
	auto xEnd = screen.Right();
	auto yStart = screen.Top();
	auto yEnd = screen.Bottom();

	for( uint32_t y = yStart; y < yEnd; ++y )
	{
		for( uint32_t x = xStart; x <= xEnd; ++x )
		{
			int index = x + ( y * size.width );

			if( index > 0 && index < size.width * size.height )
			{
				const Tile &t = tile[ index ];
				t.Draw( Cam, Gfx );
			}
		}
	}
}

cRectU TileMap::AdjustRect( const cRectU & Clip ) const
{
	return cRectU(
		Clip.Left() / tile_size,
		Clip.Top() / tile_size,
		Clip.size.width / tile_size,
		Clip.size.height / tile_size
	);
}

const BOOL TileMap::GetTile( int32_t X, int32_t Y, Tile &T )const
{	
	BOOL in_view = TRUE;
	int32_t index = X + ( Y * size.width );
	if( index < 0 || index > size.width * size.height )
	{
		return in_view;
	}

	T = tile[ index ];
	return in_view;
}
