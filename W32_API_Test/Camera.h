#pragma once

#include "CollisionRect.h"

class Camera
{
public:
	Camera(const Utilities::PointF &StartPosition, const Utilities::SizeU &ViewSize);
	~Camera();

	void Update( const cRectU &Bounds, const Utilities::PointF &FocalPoint );
	cRectU GetViewRect()const;
private:
	Utilities::PointF position;
	Utilities::SizeU size;
};

