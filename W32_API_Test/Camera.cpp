#include "Camera.h"



Camera::Camera( const Utilities::PointF &StartPosition, const Utilities::SizeU &ViewSize )
	:
	position( StartPosition ),
	size( ViewSize )
{}


Camera::~Camera()
{}

void Camera::Update( const cRectU &Bounds,
	const Utilities::PointF & FocalPoint )
{
	position.x = ( FocalPoint.x - ( static_cast<float>( size.width ) * 0.5f ) );
	position.y = ( FocalPoint.y - ( static_cast<float>( size.height ) * 0.5f ) );
		
	position.x = max( 0.f, min( position.x, Bounds.Right() - size.width - 31.f ) );
	position.y = max( 0.f, min( position.y, Bounds.Bottom() - size.height - 31.f ) );
}

cRectU Camera::GetViewRect() const
{
	auto point = Utilities::PointU(
		static_cast<uint32_t>( position.x + 0.5f ),
		static_cast<uint32_t>( position.y + 0.5f ) );

	return{point, size};
}
