#pragma once
#include "AniSprite.h"
#include "Keyboard.h"
#include "TileMap.h"
#include "Camera.h"


class Jesse
{
	enum CollisionType
	{
		Top, Bottom, Left, Right, None
	};
	enum MovementState
	{
		Standing, Running, Rolling, Jumping
	};
public:
	Jesse(Graphics &Gfx);
	~Jesse();

	Utilities::PointF GetPosition()const;
	void Update( const KeyboardClient &Kbd, float FrameTime, const TileMap &Map );
	void Draw( const Camera &Cam, Graphics &Gfx );
private:
	CollisionType CheckTopAndBottom( const Utilities::RectU &J_Clip, 
		const Utilities::RectU &T_Clip)const;
	CollisionType CheckLeftAndRight( const Utilities::RectU &J_Clip,
		const Utilities::RectU &T_Clip )const;

	Utilities::RectU GetClipRect()const;
private:
	Utilities::PointF pos, vel, max_vel;
	AniSprite stand, run, roll;
	AniSprite *cur;
	int32_t dir;
	MovementState move_state;
	BOOL on_ground;
};

