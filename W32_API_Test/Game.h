#pragma once
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <Timer.h>
#include "Jesse.h"
#include "TileMap.h"

class Game
{
public:
	Game( Graphics &Gfx, Mouse &refMouse, KeyboardServer &kServ );
	~Game();

	void Go();
private:
	void ComposeFrame();
private:
	Graphics &gfx;
	Mouse &mouse;
	KeyboardClient kbd;
	Timer t;

	Jesse jess;
	TileMap map;
	Camera cam;
};

