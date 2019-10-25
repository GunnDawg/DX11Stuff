#include "PCH.h"
#include "Core/Game.h"

Game::~Game()
{
	if (mWindow)
	{
		delete mWindow;
		mWindow = nullptr;
	}

	if (mRenderer)
	{
		delete mRenderer;
		mRenderer = nullptr;
	}
}

bool Game::Init(const WNDPROC& wndproc)
{
	Logger::Init();

	if (!mWindow->Init(wndproc))
	{
		LOG_ERROR("Failed to initialize window");
		return(false);
	}

	if (!mRenderer->Init())
	{
		LOG_ERROR("Failed to initialize renderer");
		return(false);
	}

	std::unique_ptr<GameState> S1 = std::make_unique<Scene01>();
	GSM.push(std::move(S1));

	return(true);
}

void Game::RunWindowsMessagePump()
{
	static MSG Msg = { 0 };

	while (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void Game::HandleInput()
{
	GSM.handleEvents();
}

void Game::Update()
{
	GSM.update();
}

void Game::Render()
{
	mRenderer->Clear(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	GSM.render(mRenderer);

	mRenderer->Present(GameSettings::Display::VSync);
}

void Game::ShutDown()
{
	mWindow->Shutdown();
	mRenderer->Shutdown();
}