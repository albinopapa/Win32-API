#pragma once

#include <Utilities.h>
class Camera
{
public:
	Camera(const Utilities::PointF &StartPosition, const Utilities::SizeU &ViewSize);
	~Camera();

	void Update( const Utilities::RectU &Bounds, const Utilities::PointF &FocalPoint );
	Utilities::RectU GetViewRect()const;
private:
	Utilities::PointF position;
	Utilities::SizeU size;
};

