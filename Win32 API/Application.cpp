#include "Application.h"
LRESULT Application::ProcessMessages()
{
	MSG msg{};
	LRESULT result = 0;
	quit = FALSE;
	while( !quit )
	{
		while( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			result = DispatchMessage( &msg );
		}

		Frame();
	}
	return result;
}

void Application::Quit()
{
	quit = TRUE;
}
