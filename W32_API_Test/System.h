#pragma once
#include <Application.h>
#include <AppWindow.h>
#include "Game.h"


#pragma comment(lib, "Win32 API.lib")


class System :public Application
{
public:
	System();
	~System();

	BOOL Start()override;
	void Frame()override;
	LRESULT MsgProc( const MSG &Message );

private:
	AppWindow win;
	Graphics gfx;
	MouseServer mServ;
	KeyboardServer kServ;
	Game game;
};

