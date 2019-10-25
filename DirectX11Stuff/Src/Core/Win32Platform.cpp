#include "PCH.h"
#include "Core/Game.h"
#include "Scenes/Scene02.h"

Game* game = new Game();

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;

	switch (msg)
	{
		case WM_CLOSE:
		{
			game->IsRunning = false;
		} break;

		case WM_KEYDOWN:
		{
			game->KeyBoard.OnKeyPressed(static_cast<u8>(wParam));
		} break;

		case WM_KEYUP:
		{
			game->KeyBoard.OnKeyReleased(static_cast<u8>(wParam));
		} break;

		case WM_CHAR:
		{
			game->KeyBoard.OnChar(static_cast<u8>(wParam));
		} break;

		default:
			Result = DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return(Result);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showCode)
{
	if (!game->Init(WndProc))
	{
		LOG_ERROR("Failed to intialize game");
		return(-1);
	}

	while (game->IsRunning)
	{
		game->RunWindowsMessagePump();

		game->HandleInput();
		game->Update();
		game->Render();
	}

	game->ShutDown();

	delete game;
	game = nullptr;

	return(0);
}

//Only used for debug purposes to get a console.
int main()
{
	WinMain(GetModuleHandle(0), GetModuleHandle(0), 0, SW_SHOW);
}