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

	std::wstringstream ws;

	auto f_pos = map_string.find( L'\n' ) + 1;
	std::wstring w( map_string.substr( 0, f_pos ) );
	auto wf_pos = map_string.find( L'\n', f_pos ) + 1;
	std::wstring h( map_string.substr( f_pos, wf_pos ) );
		
	ws << w;
	ws << h;
	ws >> size.width;
	ws >> size.height;

	map_string.erase( map_string.begin(), map_string.begin() + wf_pos );
	return std::move(map_string);
}

Utilities::SizeU MapLoader::Size() const
{
	return size;
}
