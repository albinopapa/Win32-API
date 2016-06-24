#pragma once
#include "Sprite.h"

class AniSprite
{
public:
	AniSprite();
	AniSprite( const std::wstring &Basename, uint32_t FrameCount, float HoldTime, const Direct2D &D2d );
	~AniSprite();

	void Advance(float FrameTime);
	void Draw( const Utilities::PointF &Position, const Graphics &Gfx );
	void DrawMirrored( const Utilities::PointF &Position, const Graphics &Gfx );
private:
	std::unique_ptr<Sprite[]> frame;
	uint32_t cur_frame, num_frames;
	float hold_time, cur_hold_time;
	
};

