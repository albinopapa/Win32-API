#include "AniSprite.h"
#include <sstream>
#include <iomanip>

AniSprite::AniSprite()
{}

AniSprite::AniSprite( const std::wstring & Basename, uint32_t FrameCount,
	float HoldTime, const Direct2D &D2d )
	:
	cur_frame( 0 ),
	num_frames( FrameCount ),
	cur_hold_time(0.0f),
	hold_time(HoldTime),
	frame( std::make_unique<Sprite[]>( FrameCount ) )
{
	for( uint32_t i = 0; i < FrameCount; ++i )
	{
		std::wstringstream ws;
		
		ws << Basename << std::setfill( L'0' ) << std::setw( 2 ) << i << L".png";
		frame[i] = Sprite( ws.str(), D2d );
	}
}


AniSprite::~AniSprite()
{}

void AniSprite::Advance( float FrameTime )
{
	cur_hold_time += FrameTime;
	if( cur_hold_time >= hold_time )
	{
		++cur_frame;
		cur_frame %= num_frames;
		cur_hold_time = 0.0f;
	}
}

void AniSprite::Draw( const Utilities::PointF & Position, const Graphics & Gfx )
{
	frame[ cur_frame ].Draw( Position, Gfx );
}

void AniSprite::DrawMirrored( const Utilities::PointF & Position, const Graphics & Gfx )
{
	frame[ cur_frame ].DrawMirrored( Position, Gfx );
}
