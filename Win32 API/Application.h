#pragma once
#include <Windows.h>
#include "Utilities.h"

#ifdef UNICODE
#pragma comment( linker, "/entry:wWinMainCRTStartup" ) 
#else
#pragma comment( linker, "/entry:WinMainCRTStartup" ) 
#endif

LRESULT CALLBACK MsgProc( HWND WinHandle, UINT Message, WPARAM wParam, LPARAM lParam );
class Application
{
public:
	Application() {}
	
	// This is the program start function defined by user
	virtual BOOL Start() = 0;
	// Message handler defined by user
	virtual LRESULT MsgProc( const MSG &Msg ) = 0;
	// This is the entry point of the program loop defined by user
	// Frame() gets called each time all messages have been processed
	virtual void Frame() = 0;
private:
#ifdef UNICODE
	friend INT WINAPI wWinMain( HINSTANCE Instance, HINSTANCE, LPWSTR CmdArgs, INT InitWinState );
#else
	friend INT WINAPI wWinMain( HINSTANCE Instance, HINSTANCE, LPSTR CmdArgs, INT InitWinState );
#endif
	static std::unique_ptr<Application> Register();
	BOOL quit;

protected:
	// Process the message loop
	LRESULT ProcessMessages();
	// Signal program to exit
	void Quit();

protected:
	HINSTANCE hInst;
	std::wstring cmd_args;
	int32_t init_win_state;
};
