#include "Camera.h"



Camera::Camera( const Utilities::PointF &StartPosition, const Utilities::SizeU &ViewSize )
	:
	position( StartPosition ),
	size( ViewSize )
{}


Camera::~Camera()
{}

void Camera::Update( const Utilities::RectU &Bounds, 
	const Utilities::PointF & FocalPoint )
{
	position.x = 
		static_cast<float>( 
			static_cast<int32_t>( FocalPoint.x ) - 
			static_cast<int32_t>( size.width / 2 ) 
			);

	position.y = 
		static_cast<float>( 
			static_cast<int32_t>( FocalPoint.y ) - 
			static_cast<int32_t>( size.width / 2 ) 
			);

	position.x = max( 0, min( position.x, Bounds.Right() - size.width ) );
	position.y = max( 0, min( position.y, Bounds.Bottom() - size.height ) );
}

Utilities::RectU Camera::GetViewRect() const
{
	auto point_u = Utilities::PointU(
		static_cast<uint32_t>( position.x ),
		static_cast<uint32_t>( position.y ) );

	return Utilities::RectU( point_u, size );
}
