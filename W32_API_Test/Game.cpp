#include "Game.h"



Game::Game( Graphics &Gfx, Mouse &refMouse, KeyboardServer &kServ )
	:
	gfx( Gfx ),
	mouse( refMouse ),
	kbd( kServ ),
	jess( gfx ),
	map( L"Maps/level0000.txt" ),
	cam( Utilities::PointF(), Utilities::SizeU( 800, 600 ) )
{}


Game::~Game()
{}

void Game::Go()
{
	t.Stop();
	float dt = t.GetMilli();
	t.Start();

	auto world_bounds = map.GetWorldBounds();
	jess.Update( kbd, dt, map );
	cam.Update( world_bounds, jess.GetPosition() );

	auto j_rect = jess.GetClipRect();

	if( j_rect.Bottom() >= world_bounds.Bottom() )
	{

		jess.Reset();
	}

	gfx.BeginFrame( 0x007FFFu );
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ComposeFrame()
{
	gfx.DrawGradientRect( Utilities::RectF( 0.f, 0.f, 800.f, 600.f ),
		D2D1::ColorF::White, D2D1::ColorF::White );
	map.Draw( cam, gfx );
	jess.Draw( cam, gfx );
}
