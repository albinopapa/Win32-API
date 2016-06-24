#include "Game.h"



Game::Game( Graphics &Gfx, MouseServer &mServ, KeyboardServer &kServ )
	:
	gfx( Gfx ),
	mouse( mServ ),
	kbd( kServ ),
	jess( gfx ),
	map( L"Maps/test.txt" ),
	cam( Utilities::PointF(), Utilities::SizeU( 800, 600 ) )
{}


Game::~Game()
{}

void Game::Go()
{
	t.Stop();
	float dt = t.GetMilli();
	t.Start();

	jess.Update( kbd, dt, map );
	cam.Update( map.GetWorldBounds(), jess.GetPosition() );

	gfx.BeginFrame( D2D1::ColorF( D2D1::ColorF::Navy ) );
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ComposeFrame()
{
	map.Draw( cam, gfx );
	jess.Draw( cam, gfx );
}
