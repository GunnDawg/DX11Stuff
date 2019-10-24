#pragma once
#include "Core/GameState.h"
#include "Graphics/Renderer.h"

class Scene02 : public GameState
{
public:
	void on_enter() override;
	void on_exit() override;
	void update() override;
	void handle_events() override;
	void render(Renderer* renderer) override;

private:

};