#pragma once
#include <string>

class MapLoader
{
public:
	MapLoader();
	~MapLoader();
	std::wstring operator( )( const std::wstring &Filename );

private:
	std::wstring map_string;
};

