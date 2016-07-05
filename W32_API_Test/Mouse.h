/****************************************************************************************** 
 *	Chili DirectX Framework Version 14.03.22											  *	
 *	Mouse.h																				  *
 *	Copyright 2014 PlanetChili <http://www.planetchili.net>								  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once
#include <queue>

class Mouse
{
	friend class System;
public:
	class Event
	{
	public:
		enum Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Invalid
		};
	private:
		Type type;
		int x;
		int y;
	public:
		constexpr Event( Type type,int x,int y )
			:
			type( type ),
			x( x ),
			y( y )
		{}
		constexpr bool IsValid() const
		{
			return type != Invalid;
		}
		constexpr Type GetType() const
		{
			return type;
		}
		constexpr std::pair<int,int> GetPos() const
		{
			return{ x,y };
		}
	};
public:
	std::pair<int,int> GetPos() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	bool IsInWindow() const;
	Mouse::Event ReadMouse();
	bool BufferIsEmpty() const;
	void ClearBuffer();
private:
	void OnMouseMove( int x,int y );
	void OnMouseLeave();
	void OnMouseEnter();
	void OnLeftPressed( int x,int y );
	void OnLeftReleased( int x,int y );
	void OnRightPressed( int x,int y );
	void OnRightReleased( int x,int y );
	void OnWheelUp( int x,int y );
	void OnWheelDown( int x,int y );
	void TrimBuffer();
private:
	static constexpr unsigned int bufferSize = 4u;
	int x;
	int y;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool isInWindow = false;
	std::queue<Event> buffer;
};