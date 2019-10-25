#include "PCH.h"
#include "Scene01.h"
#include "Core/Game.h"

void Scene01::on_enter()
{
	
}

void Scene01::on_exit()
{

}

void Scene01::update()
{

}

void Scene01::handle_events()
{
	if (Game::KeyBoard.KeyIsPressed(VK_ESCAPE))
	{
		Game::IsRunning = false;
	}
}

void Scene01::render(Renderer* renderer)
{

}