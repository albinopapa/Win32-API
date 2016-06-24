#include "Jesse.h"



Jesse::Jesse( Graphics &Gfx )
	:
	stand( L"Images\\Stand\\stand", 1, 1000.0f, Gfx.GetDirect2D() ),
	run( L"Images\\Run\\run", 15, 18.f, Gfx.GetDirect2D() ),
	roll( L"Images\\Roll\\roll", 15, 18.f, Gfx.GetDirect2D() ),
	cur( &stand ),
	dir(1),
	move_state(Standing),
	on_ground(FALSE)
{}


Jesse::~Jesse()
{}

Utilities::PointF Jesse::GetPosition() const
{
	return pos;
}

void Jesse::Update( const KeyboardClient & Kbd, float FrameTime, const TileMap &Map )
{
	cur = &stand;
	float speed = 6.0f;
	float grav = 9.8f * 0.16f * 0.16f;

	Utilities::PointF accel( 0.0f, grav );

	if( Kbd.KeyIsPressed( VK_LEFT ) || Kbd.KeyIsPressed( VK_RIGHT ) )
	{
		move_state = Kbd.KeyIsPressed( VK_CONTROL ) ? 
			Rolling :									// Control button pressed
			move_state == Standing ?					// Control button not pressed
			Running										// move_state is Standing	
			: move_state;								// move_state is not Standing

		cur = move_state == Rolling ? &roll : &run;
		dir = Kbd.KeyIsPressed( VK_LEFT ) ? -1 : 1;

		cur->Advance( FrameTime );
		accel.x += speed * dir;
	}
	else
	{
		accel.x += move_state == Jumping ? 0.0f : -vel.x;

		move_state = vel.y == 0.0f ?
			accel.x == 0.0f ?							// vel.y == 0.0f
			Standing									// accel.x is 0.0f
			: Running									// accel.x is not 0.0f
			: move_state;								// vel.y != 0.0f
	}
	if( Kbd.KeyIsPressed( VK_SPACE ) )
	{
		if( on_ground )
		{
			move_state = Jumping;
			vel.y -= 8.0f;
			on_ground = FALSE;
		}
	}

	auto j_clip = GetClipRect();
	{
		auto tiles = Map.GetClipRects( j_clip );

		for( auto& tile : tiles )
		{
			auto t_clip = tile.GetClipInPixels();
			auto t_type = tile.GetType();

			{
				switch( t_type )
				{
					case Ceiling:
					{
						auto c_type = CheckTopAndBottom( j_clip, t_clip );
						if( c_type == Top )
						{
							j_clip.position.y = t_clip.Bottom();
							accel.y = -vel.y;
						}
						break;
					}
					case Floor:
					{
						auto c_type = CheckTopAndBottom( j_clip, t_clip );
						if( c_type == Bottom )
						{
							j_clip.position.y = t_clip.position.y - static_cast<int32_t>( j_clip.size.height );
							accel.y = -vel.y;
							on_ground = TRUE;
						}
						break;
					}
					case Wall:
					{
						auto c_type = CheckLeftAndRight( j_clip, t_clip );

						if( c_type == Left )
						{
							if( dir > 0 )
							{
								j_clip.position.x = t_clip.position.x - static_cast<int32_t>( j_clip.size.width );
							}
							accel.x = -vel.x;
						}
						else if( c_type == Right )
						{
							j_clip.position.x = t_clip.Right();
							accel.x = -vel.x;
						}
						break;
					}
					case NotPassable:
					{
						auto c_type = CheckLeftAndRight( j_clip, t_clip );

						if( c_type == Top )
						{
							j_clip.position.y = t_clip.Bottom();
							accel.y = -vel.y;
						}
						else if( c_type == Bottom )
						{
							j_clip.position.y = t_clip.position.y - static_cast<int32_t>( j_clip.size.height );
							accel.y = -vel.y;
							on_ground = TRUE;
						}

						c_type = CheckTopAndBottom( j_clip, t_clip );
						if( c_type == Left )
						{
							if( dir > 0 )
							{
								j_clip.position.x = t_clip.position.x - static_cast<int32_t>( j_clip.size.width );
							}
							accel.x = -vel.x;
						}
						else if( c_type == Right )
						{
							j_clip.position.x = t_clip.Right();
							accel.x = -vel.x;
						}
						break;
					}
				}
			}
		}
	}

	// Update position
	pos.x = static_cast<float>( j_clip.position.x - static_cast<int32_t>( j_clip.size.width / 2 ) );
	pos.y = static_cast<float>( j_clip.position.y );

	// Add acceleration to velocity
	vel.x += accel.x;
	vel.y += accel.y;

	// Cap velocity
	vel.x = max( -speed, min( speed, vel.x ) );
	vel.y = max( -64.0f, min( 64.0f, vel.y ) );
	
	// Add velocity to position
	pos.x += vel.x;
	pos.y += vel.y;

	// Clamp sprite to world coordinates
	auto bounds = Map.GetWorldBounds();
	auto bounds_right = bounds.Right() - 1 - j_clip.size.width;
	auto bounds_bottom = bounds.Bottom() - 1 - j_clip.size.height;

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

Jesse::CollisionType Jesse::CheckTopAndBottom( const Utilities::RectU &J_Clip,
	const Utilities::RectU &T_Clip ) const
{
	CollisionType type = None;
	uint32_t j_top = J_Clip.position.y;
	uint32_t j_bottom = J_Clip.Bottom();
	uint32_t t_top = T_Clip.position.y;
	uint32_t t_bottom = T_Clip.Bottom();

	if( j_top > t_top  && j_top < t_bottom)
	{
		type = Top;
	}
	else if( j_bottom > t_top  && j_bottom < t_bottom )
	{
		type = Bottom;
	}

	return type;
}

Jesse::CollisionType Jesse::CheckLeftAndRight( const Utilities::RectU &J_Clip,
	const Utilities::RectU &T_Clip ) const
{
	CollisionType type = None;
	uint32_t j_left = J_Clip.position.x;
	uint32_t j_right = J_Clip.Right();
	uint32_t t_left = T_Clip.position.x;
	uint32_t t_right = T_Clip.Right();

	if( j_left > t_left && j_left < t_right )
	{
		type = Left;
	}
	if( j_right > t_left && j_right < t_right )
	{
		type = Right;
	}

	return type;
}

Utilities::RectU Jesse::GetClipRect() const
{
	return Utilities::RectU( Utilities::PointU(
		static_cast<uint32_t>( pos.x + 32.0f + 0.5f ),
		static_cast<uint32_t>( pos.y + 0.5f ) ),
		Utilities::SizeU( 64, 128 ) );
}
