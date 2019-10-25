#pragma once
#include <memory>
#include "Core/Window.h"
#include "Graphics/Renderer.h"
#include "Core/GameStateMachine.h"
#include "Input/Keyboard.h"
#include "Scenes/Scene01.h"

struct Game
{
	~Game();

	bool Init(const WNDPROC& wndproc);

	void RunWindowsMessagePump();
	void HandleInput();
	void Update();
	void Render();

	void ShutDown();

	Window* mWindow = new Window();
	Renderer* mRenderer = new Renderer();
	inline static Keyboard KeyBoard;
	inline static GameStateMachine GSM = GameStateMachine();

	inline static bool IsRunning = true;
};