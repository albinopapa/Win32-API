#include "MapLoader.h"
#include <fstream>


MapLoader::MapLoader()
{}


MapLoader::~MapLoader()
{}

std::wstring MapLoader::operator()( const std::wstring & Filename ) 
{
	std::ifstream file( Filename );
	if( file.is_open() )
	{
		while( !file.eof() )
		{
			map_string.push_back(file.get());
		}
	}
	file.close();
	return std::move(map_string);
}
