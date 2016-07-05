#include "Jesse.h"
#include <dinput.h>


Jesse::Jesse( Graphics &Gfx )
	:
	size( 64, 128 ),
	stand( L"Images\\Stand\\stand", 1, 1000.0f, Gfx.GetDirect2D() ),
	run( L"Images\\Run\\run", 15, 18.f, Gfx.GetDirect2D() ),
	roll( L"Images\\Roll\\roll", 15, 18.f, Gfx.GetDirect2D() )
{
	Reset();
}


Jesse::~Jesse()
{}

void Jesse::Reset()
{
	pos.x = 0.f;
	pos.y = 288.f;
	SetMoveState( Standing );
	on_ground = FALSE;
	force_roll = FALSE;
	dir = 1;
}

Utilities::PointF Jesse::GetPosition() const
{
	return pos;
}

void Jesse::Update( const KeyboardClient & Kbd, float FrameTime, const TileMap &Map )
{
	float speed = 6.0f;
	const float grav = 9.8f * 0.16f * 0.16f;
	Utilities::PointF accel( 0.0f, grav );
	BOOL ceil_handled = FALSE,
		floor_handled = FALSE,
		wall_handled = FALSE,
		npass_handled = FALSE;
	BOOL in_ceiling = FALSE;

	// Cap velocity
	const float cap_x_speed = speed * 2.0f;
	vel.x = max( -cap_x_speed, min( cap_x_speed, vel.x ) );
	vel.y = max( -64.0f, min( 64.0f, vel.y ) );

	// Add velocity to position
	pos.x += vel.x;
	pos.y += vel.y;

	MovementState prev_state = move_state;

	// Update state
	if( Kbd.KeyIsPressed( VK_LEFT ) || Kbd.KeyIsPressed( VK_RIGHT ) )
	{
		dir = Kbd.KeyIsPressed( VK_LEFT ) ? -1 : 1;
		if( Kbd.KeyIsPressed( VK_CONTROL ) )
		{
			SetMoveState( Rolling );
		}
		else
		{
			if( !force_roll )
			{
				SetMoveState( Running );
			}
		}

		cur->Advance( FrameTime );
		accel.x += on_ground ? speed * dir : ( speed * 0.1f ) * dir;
	}
	else
	{
		if( on_ground )
		{
			accel.x += -vel.x;
			if( accel.x == 0.0f )
			{
				if( !force_roll )
				{
					SetMoveState( Standing );
				}
			}
		}
		else
		{
			accel.x += -( vel.x * 0.5f );
		}
	}
	if( Kbd.KeyIsPressed( VK_SPACE ) && on_ground )
	{
		if( !force_roll )
		{
			SetMoveState( Jumping );
		}
	}

	// Get collision rect and tiles
	auto j_clip = GetClipRect();
	auto tiles = Map.GetClipRects<float>( j_clip );
	
	force_roll = force_roll && Map.IsUnderCeilingTiles( 
		CollisionRect<float>( j_clip.position.x, j_clip.position.y - 30.f, j_clip.size.width, 32.f )
	) ? TRUE : FALSE;

	auto DoWallCollision = [&]( const cRectU & T_Clip )->void
	{
		if( !wall_handled )
		{
			if( j_clip.Right() > T_Clip.Left() &&
				j_clip.Right() < T_Clip.Right() )
			{
				wall_handled = TRUE;
				j_clip.position.x = T_Clip.Left() - ( j_clip.size.width );
				accel.x = -vel.x;
			}
			else if( j_clip.Left() < T_Clip.Right() &&
				j_clip.Left() > T_Clip.Left() )
			{
				wall_handled = TRUE;
				j_clip.position.x = T_Clip.Right();
				accel.x = -vel.x;
			}
		}
	};
	auto DoCeilingCollision = [&]( const cRectU & T_Clip )->void
	{
		if( !ceil_handled )
		{
			in_ceiling = TRUE;
			ceil_handled = TRUE;			
			if( prev_state == Rolling && move_state != prev_state )
			{
				SetMoveState( Rolling );
				j_clip.size.height = size.height;
				force_roll = TRUE;
			}
			j_clip.position.y = T_Clip.Bottom();
			accel.y = -vel.y;
		}
	};
	auto DoFloorCollision = [&]( const cRectU &T_Clip )->void
	{
		if( !floor_handled )
		{
			if( j_clip.Bottom() > T_Clip.Top() &&
				j_clip.Bottom() < T_Clip.Bottom() &&
				vel.y >= 0.0f )
			{
				if( in_ceiling && move_state == Standing )
				{
					SetMoveState( Rolling );
					force_roll = TRUE;
				}

				floor_handled = TRUE;
				j_clip.position.y = T_Clip.position.y - j_clip.size.height;
				accel.y = vel.y > 0.0f ? -vel.y : accel.y;
				on_ground = TRUE;
			}
		}
	};

	for( auto& tile : tiles )
	{
		auto t_clip = tile.GetClipInPixels();
		auto t_type = tile.GetType();
				
		if( CheckCollision( j_clip, t_clip ) )
		{
			if( t_type == Wall )
			{
				DoWallCollision( t_clip );
			}
			if( t_type == Ceiling )
			{
				DoCeilingCollision( t_clip );
			}
			if( t_type == Floor )
			{
				DoFloorCollision( t_clip );
			}
			if( t_type == NotPassable )
			{
				if( force_roll )
				{
					int a = 0;
				}
				if( dir > 0 )
				{
					auto px = static_cast<int32_t>( j_clip.Right() - t_clip.Left() );
					auto tpy = static_cast<int32_t>( j_clip.Bottom() - t_clip.Top() );
					auto bpy = static_cast<int32_t>( j_clip.Top() - t_clip.Bottom() );

					if( px * vel.y > tpy * vel.x )
					{
						DoFloorCollision( t_clip );
					}
					else if( px * -vel.y > bpy * vel.x && bpy > vel.y )
					{
						DoCeilingCollision( t_clip );
					}
					else
					{
						DoWallCollision( t_clip );
					}
				}
				else
				{
					auto px = static_cast<int32_t>( t_clip.Right() - j_clip.Left() );
					auto tpy = static_cast<int32_t>( j_clip.Bottom() - t_clip.Top() );
					auto bpy = static_cast<int32_t>( j_clip.Top() - t_clip.Bottom() );

					if( px * vel.y > tpy * -vel.x )
					{
						DoFloorCollision( t_clip );
					}
					else if( px * -vel.y > bpy * -vel.x && bpy > vel.y )
					{
						DoCeilingCollision( t_clip );
					}
					else
					{
						DoWallCollision( t_clip );
					}
				}
			}
		}
	}

	// Update position
	pos.x = j_clip.position.x - ( j_clip.size.width * 0.5f );
	pos.y = move_state != Rolling ? j_clip.position.y : j_clip.position.y - j_clip.size.height;

	// Add acceleration to velocity
	vel.x += accel.x;
	vel.y += accel.y;

	// Clamp sprite to world coordinates
	auto bounds = Map.GetWorldBounds();
	auto bounds_right = bounds.Right() - (j_clip.size.width * 2.f);
	auto bounds_bottom = bounds.Bottom() - (j_clip.size.height);

	pos.x = max( bounds.position.x, min( bounds_right, pos.x ) );
	pos.y = max( bounds.position.y, min( bounds_bottom, pos.y ) );
}

void Jesse::Draw( const Camera &Cam, Graphics & Gfx )
{
	auto view = Cam.GetViewRect();
	Utilities::PointF d_pos( pos.x - view.position.x, pos.y - view.position.y );

	if( dir > 0 )
	{
		cur->Draw( d_pos, Gfx );
	}
	else
	{
		cur->DrawMirrored( d_pos, Gfx );
	}
}

void Jesse::SetMoveState( MovementState State )
{
	if( move_state != State )
	{
		move_state = State;
		size.height = 128;

		switch( move_state )
		{
			case Standing:
				cur = &stand;
				break;
			case Running:
				cur = &run;
				break;
			case Rolling:
				cur = &roll;
				size.height = 64;
				break;
			case Jumping:
				vel.y -= 9.0f;
				on_ground = FALSE;
				break;
		}

		cur->ResetAnimation();
	}
}

BOOL Jesse::CheckCollision( const CollisionRect<float>& J_Clip, const CollisionRect<uint32_t>& T_Clip ) const
{
	BOOL collide =
		J_Clip.Right() > T_Clip.Left() &&
		J_Clip.Left() < T_Clip.Right() &&
		J_Clip.Bottom() > T_Clip.Top() &&
		J_Clip.Top() < T_Clip.Bottom();

	return collide;
}

CollisionRect<float> Jesse::GetClipRect() const
{
	CollisionRect<float> rect;

	rect.size.width = size.width;
	rect.size.height = size.height;

	rect.position.x = pos.x + 32.f;
	rect.position.y = pos.y + ( 128.f - rect.size.height );

	return rect;
}
