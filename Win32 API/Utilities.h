#pragma once
#include <intrin.h>
#include <memory>
#include <string>
#include <wrl.h>
#include <assert.h>
#include <d2d1_2.h>

using sp128_t = __m128;
using int128_t = __m128i;
using dp128_t = __m128d;

template<class T>
using uptr = std::unique_ptr<T>;
template <class T>
using comptr = Microsoft::WRL::ComPtr<T>;


namespace Utilities
{
	template<class T>
	struct SizeT
	{
		SizeT()
			:
			width( 0 ),
			height( 0 ) 
		{}
		SizeT( T Width, T Height )
			:
			width( Width ),
			height( Height )
		{}

		T width, height;
	};
	
	template<class T>
	struct PointT
	{
		PointT():x( 0 ), y( 0 ) {}
		PointT( T X, T Y )
			:
			x( X ), 
			y( Y )
		{}

		T x, y;
	};
	
	template<class T>
	struct RectT
	{
		RectT() {}
		RectT( T X, T Y, T Width, T Height )
			:
			position( PointT<T>( X, Y ) ),
			size( SizeT<T>( Width, Height ) )
		{}
		RectT( const PointT<T> &Pos, const SizeT<T> &Size )
			:
			position( Pos ),
			size( Size )
		{}
		operator D2D1_RECT_U()const
		{
			return D2D1_RECT_U{
				static_cast<uint32_t>( position.x ), 
				static_cast<uint32_t>( position.y),
				static_cast<uint32_t>( Right() ), 
				static_cast<uint32_t>( Bottom() )
			}
		}
		operator D2D1_RECT_F()const
		{
			return D2D1_RECT_F{
				static_cast<float>( position.x ),
				static_cast<float>( position.y ),
				static_cast<float>( Right() ),
				static_cast<float>( Bottom() )
			};
		}
		T Right()const
		{
			return position.x + size.width;
		}
		T Bottom()const
		{
			return position.y + size.height;
		}

		PointT<T> position;
		SizeT<T> size;
	};

	using PointU = PointT<uint32_t>;
	using PointF = PointT<float>;
	using SizeU = SizeT<uint32_t>;
	using SizeF = SizeT<float>;
	using RectU = RectT<uint32_t>;
	using RectF = RectT<float>;
}

