#pragma once
#include <Direct2D.h>
#include <Utilities.h>

class Graphics
{
public:
	Graphics(const AppWindow &Win);
	~Graphics();

	const Direct2D &GetDirect2D()const;
	void BeginFrame( const D2D1::ColorF &Color );
	void EndFrame();
	void DrawFilledRect( const Utilities::RectU &Rect, const D2D1::ColorF &Color )const;
	void DrawBitmap( const Utilities::PointT<float> &Position, ID2D1Bitmap1 *Bitmap )const;
	void DrawBitmapMirrored( const Utilities::PointT<float> &Position, ID2D1Bitmap1 *Bitmap )const;
private:
	Direct2D d2d;
	comptr<ID2D1DrawingStateBlock1> pState;
	comptr<ID2D1SolidColorBrush> brush;
};

