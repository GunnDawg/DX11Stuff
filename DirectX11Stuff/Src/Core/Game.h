#pragma once
#include <memory>
#include "Graphics/Renderer.h"
#include "Core/Window.h"
#include "Core/GameStateMachine.h"
#include "Scenes/Scene01.h"

struct Game
{
	~Game();

	bool Init(WNDPROC wndproc);

	void RunWindowsMessagePump();
	void HandleInput();
	void Update();
	void Render();

	void ShutDown();

	bool IsRunning = true;

	Window* mWindow = new Window();
	Renderer* mRenderer = new Renderer();
	GameStateMachine GSM = GameStateMachine();
};