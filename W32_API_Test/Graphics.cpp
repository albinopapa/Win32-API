#include "Graphics.h"
#include <assert.h>
#include <vector>

Graphics::Graphics( const AppWindow &Win )
	:
	d2d(Win)
{
	pState = d2d.CreateDrawingStateBlock();
	brush = d2d.CreateSolidColorBrush();
	
	// Create sky gradients
	{
		// Setup variables
		std::vector<D2D1_GRADIENT_STOP> stops;
		stops.push_back( D2D1::GradientStop( 0.f, D2D1::ColorF( D2D1::ColorF::Black,0.f ) ) );
		stops.push_back( D2D1::GradientStop( 1.0f, D2D1::ColorF( D2D1::ColorF::White ) ) );

		auto stop_coll = d2d.CreateGradientStopCollection( stops );
		lingrad_brush = d2d.CreateLinearGradientBrush( stop_coll.Get(),
			Utilities::RectF( 0.f, 0.f, 0.f, Win.Size().height ) );
	}
}


Graphics::~Graphics()
{}

const Direct2D & Graphics::GetDirect2D() const
{
	return d2d;
}

void Graphics::BeginFrame( const D2D1::ColorF Color )
{
	auto context = d2d.GetContext();

	context->BeginDraw();
	context->Clear( Color );
}

void Graphics::EndFrame()
{
	auto context = d2d.GetContext();
	auto swap_chain = d2d.GetSwapchain();

	HRESULT hr = context->EndDraw();
	assert( SUCCEEDED( hr ) );

	hr = swap_chain->Present( 1, DXGI_PRESENT_DO_NOT_WAIT );
	assert( SUCCEEDED( hr ) );
}

void Graphics::DrawGradientRect( const Utilities::RectF & Rect, const D2D1::ColorF Start, const D2D1::ColorF Stop )
{
	auto context = d2d.GetContext();
	D2D1_RECT_F rect( Rect );
	context->FillRectangle( rect, lingrad_brush.Get() );
}

void Graphics::DrawFilledRect( const Utilities::RectF & Rect, const D2D1::ColorF & Color ) const
{
	auto context = d2d.GetContext();
	D2D1_RECT_F rect( Rect );
	brush->SetColor( Color );
	context->FillRectangle( rect, brush.Get());
}

void Graphics::DrawBitmap( const Utilities::PointT<float> &Position, ID2D1Bitmap1 * Bitmap )const
{
	auto context = d2d.GetContext();
	auto size = Bitmap->GetPixelSize();	
	D2D1_RECT_F rect = D2D1::RectF( Position.x, Position.y, 
		Position.x + size.width, Position.y + size.height );
	context->DrawBitmap(Bitmap, rect );
}

void Graphics::DrawBitmapMirrored( const Utilities::PointT<float>& Position, ID2D1Bitmap1 * Bitmap ) const
{
	auto context = d2d.GetContext();
	auto size = Bitmap->GetPixelSize();
	D2D1_MATRIX_3X2_F trans = D2D1::Matrix3x2F::Scale( 
		-1.0f, 1.0f, D2D1::Point2F( Position.x + 64.0f, Position.y + 64.0f ) );
	D2D1_RECT_F rect = D2D1::RectF( Position.x, Position.y,
		Position.x + size.width, Position.y + size.height );

	context->SaveDrawingState( pState.Get() );
	context->SetTransform( trans );
	context->DrawBitmap( Bitmap, rect );
	//context->SetTransform( D2D1::Matrix3x2F::Identity() );
	context->RestoreDrawingState( pState.Get() );
}
