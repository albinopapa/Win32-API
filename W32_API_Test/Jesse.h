#pragma once
#include "AniSprite.h"
#include "Keyboard.h"
#include "TileMap.h"
#include "Camera.h"
#include "GameObject.h"


class Jesse :public GameObject
{
	enum MovementState
	{
		Standing, Running, Rolling, Jumping
	};
public:
	Jesse(Graphics &Gfx);
	~Jesse();

	Utilities::PointF GetPosition()const;
	CollisionRect<float> GetClipRect()const;

	void Reset()override;
	void Update( const KeyboardClient &Kbd, float FrameTime, const TileMap &Map );
	void Draw( const Camera &Cam, Graphics &Gfx );
private:
	void SetMoveState( MovementState State );
	BOOL CheckCollision( const CollisionRect<float> &J_Clip,
		const CollisionRect<uint32_t> &T_Clip )const;
	
private:
	Utilities::PointF pos, vel;
	Utilities::SizeU size;
	AniSprite stand, run, roll;
	AniSprite *cur;
	int32_t dir;
	MovementState move_state;
	BOOL on_ground, force_roll;
};

