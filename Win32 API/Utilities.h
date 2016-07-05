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

enum class WindowMessage
{
	CREATE			= WM_CREATE,
	MOVE			= WM_MOVE,
	SIZE			= WM_SIZE,
	DESTROY			= WM_DESTROY, 
	CLOSE			= WM_CLOSE,
	QUIT			= WM_QUIT,
	KEY_DOWN		= WM_KEYDOWN,
	KEY_UP			= WM_KEYUP,
	L_BUTTON_DOWN	= WM_LBUTTONDOWN, 
	L_BUTTON_UP		= WM_LBUTTONUP,
	R_BUTTON_DOWN	= WM_RBUTTONDOWN,
	R_BUTTON_UP		= WM_RBUTTONUP,
	WHEEL			= WM_MOUSEWHEEL
};

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
		SizeT( const SizeT<T> &Right )
			:
			width( Right.width ),
			height( Right.height )
		{}
		SizeT(SizeT<T>&& Right)
			:
			width( Right.width ),
			height( Right.height )
		{}
		SizeT<T> &operator=( const SizeT<T> &Right )
		{
			width = Right.width;
			height = Right.height;
			return *this;
		}
		SizeT<T> &operator=( SizeT<T>&& Right )
		{
			width = Right.width;
			height = Right.height;
			return *this;
		}

		T width, height;
	};
	
	template<class T>
	struct PointT
	{
		PointT()
			:
			x( 0 ), 
			y( 0 ) 
		{}
		PointT( T X, T Y )
			:
			x( X ), 
			y( Y )
		{}
		PointT( const PointT<T> &Right )
			:
			x( Right.x ),
			y( Right.y )
		{}
		PointT(PointT<T>&& Right)
			:
			x( Right.x ),
			y( Right.y )
		{}
		PointT<T> &operator=( const PointT<T>& Right )
		{
			x = Right.x;
			y = Right.y;
			return *this;
		}
		PointT<T> &operator=( PointT<T>&& Right)
		{
			x = Right.x;
			y = Right.y;
			return *this;
		}


		T x, y;
	};
	
	template<class T>
	struct RectT
	{
		RectT() {}
		RectT( T X, T Y, T Width, T Height )
			:
			position( X, Y ),
			size( Width, Height )
		{}
		RectT( const PointT<T> &Pos, const SizeT<T> &Size )
			:
			position( Pos ),
			size( Size )
		{}
		RectT( const RectT<T> &Right )
			:
			position( Right.position ),
			size( Right.size )
		{}
		RectT( RectT<T> &&Right)
			:
			position( Right.position ),
			size( Right.size )
		{}

		template<class U>
		operator RectT<U>()
		{
			return RectT<U>(
				static_cast<U>( position.x ),
				static_cast<U>( position.y ),
				static_cast<U>( size.width ),
				static_cast<U>( size.height )
				);
		}
		operator D2D1_RECT_L()const
		{
			return D2D1_RECT_L(
				static_cast<long>( position.x ),
				static_cast<long>( position.y ),
				static_cast<long>( Right() ),
				static_cast<long>( Bottom() )
			);
		}
		operator D2D1_RECT_U()const
		{
			return D2D1_RECT_U{
				static_cast<uint32_t>( position.x ),
				static_cast<uint32_t>( position.y ),
				static_cast<uint32_t>( Right() ),
				static_cast<uint32_t>( Bottom() )
			};
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

		RectT<T> &operator=( const RectT<T> &Right )
		{
			position = Right.position;
			size = Right.size;
			return *this;
		}
		RectT<T> &operator=( RectT<T> &&Right )
		{
			position = Right.position;
			size = Right.size;
			return *this;
		}

		T Left()const
		{
			return position.x;
		}
		T Right()const
		{
			return position.x + size.width;
		}
		T Top()const
		{
			return position.y;
		}
		T Bottom()const
		{
			return position.y + size.height;
		}

		PointT<T> TopLeft()const
		{
			return PointT<T>( Left(), Top() );
		}
		PointT<T> TopRight()const
		{
			return PointT<T>( Right(), Top() );
		}
		PointT<T> BottomLeft()const
		{
			return PointT<T>( Left(), Bottom() );
		}
		PointT<T> BottomRight()const
		{
			return PointT<T>( Right(), Bottom() );
		}


		PointT<T> position;
		SizeT<T> size;
	};

	inline uint16_t LoWord( const int32_t Val )
	{
		return static_cast<uint16_t>( Val & 0x0000FFFF );
	}
	inline uint16_t HiWord( const int32_t Val )
	{
		return LoWord( Val >> 16 );
	}
	
	constexpr uint32_t uint_max = UINT_MAX;
	constexpr int32_t int_max = INT_MAX;
	

	using PointU = PointT<uint32_t>;
	using PointF = PointT<float>;
	using PointL = PointT<int32_t>;
	using SizeU = SizeT<uint32_t>;
	using SizeF = SizeT<float>;
	using SizeL = SizeT<int32_t>;
	using RectU = RectT<uint32_t>;
	using RectF = RectT<float>;
	using RectL = RectT<int32_t>;
}

