#pragma once
#include <Utilities.h>

template<class T>
class CollisionRect : public Utilities::RectT<T>
{
public:
	CollisionRect()
	{}
	CollisionRect( T X, T Y, T Width, T Height )
		:
		Utilities::RectT<T>(X, Y, Width, Height)
	{}
	CollisionRect( const Utilities::PointT<T> &Pos, const Utilities::SizeT<T> &Size )
		:
		Utilities::RectT<T>(Pos, Size)
	{}
	CollisionRect( const CollisionRect<T> &Right )
		:
		Utilities::RectT<T>(Right.position, Right.size)
	{}
	CollisionRect( CollisionRect<T> &&Right )
		:
		Utilities::RectT<T>( Right.position, Right.size )
	{}

	CollisionRect<T> &operator=( const CollisionRect<T> &Right )
	{
		position = Right.position;
		size = Right.size;
		return *this;
	}
	CollisionRect<T> &operator=( CollisionRect<T> &&Right )
	{
		position = Right.position;
		size = Right.size;
		return *this;
	}

	~CollisionRect()
	{}

	BOOL ContainsPoint( const Utilities::PointT<T> &Point )
	{
		BOOL contained =
			Point.x > Left() && Point.x < Right() &&
			Point.y > Top() && Point.y < Bottom();

		return contained;
	}
	BOOL Intersects( const Utilities::RectT<T> &Rect )
	{
		BOOL intersects =
			Rect.Left() < Right() && Rect.Right() > Left() &&
			Rect.Top() < Bottom() && Rect.Bottom() > Top();

		return intersects;
	}
	BOOL Intersects( const Utilities::PointT<T> &P0, const Utilities::PointT<T> &P1 )
	{
		BOOL intersects = ContainsPoint( P0 ) || ContainsPoint( P1 );
		// TODO: Learn how to do physics
		return intersects;
	}

};

using cRectU = CollisionRect<uint32_t>;