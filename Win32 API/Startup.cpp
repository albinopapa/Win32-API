#include "Application.h"

#ifdef UNICODE
INT WINAPI wWinMain( HINSTANCE Instance, HINSTANCE, LPWSTR CmdArgs, INT InitWinState )
{
	std::unique_ptr<Application> app = Application::Register();
	app->cmd_args = std::wstring( CmdArgs );
	app->hInst = Instance;
	app->init_win_state = InitWinState;

	BOOL was_success = app->Start();
	if( !was_success )
	{
		return -1;
	}

	LRESULT res = app->ProcessMessages();
	return res;
}
#else // #elif !defined UNICODE
INT WINAPI WinMain( HINSTANCE Instance, HINSTANCE, LPSTR CmdArgs, INT InitWinState )
{
	std::unique_ptr<Application> app = Application::Register();
	std::string c_args( CmdArgs );
	app->cmd_args = std::wstring( c_args.begin(), c_args.end() );
	app->hInst = Instance;
	app->init_win_state = InitWinState;

	int res = app->Start();
	return res;
}
#endif

LRESULT CALLBACK MsgProc( HWND WinHandle, UINT Message, WPARAM wParam, LPARAM lParam )
{
	LRESULT result = 0;
	Application *app = reinterpret_cast<Application*>( GetWindowLongPtr( WinHandle, GWLP_USERDATA ) );

	if( app )
	{
		MSG msg{};
		msg.lParam = lParam;
		msg.message = Message;
		msg.wParam = wParam;

		app->MsgProc( msg );
	}
	else
	{
		result = DefWindowProc( WinHandle, Message, wParam, lParam );
	}

	return result;
}
