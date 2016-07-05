#pragma once
#include <string>
#include <Utilities.h>
#include <sstream>

class MapLoader
{
public:
	MapLoader();
	~MapLoader();
	std::wstring operator( )( const std::wstring &Filename );
	Utilities::SizeU Size()const;
private:
	std::wstring map_string;
	Utilities::SizeU size;
};

