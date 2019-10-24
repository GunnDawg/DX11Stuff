#include "PCH.h"
#include "Scene01.h"

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

}

void Scene01::render(Renderer* renderer)
{
	renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);

	renderer->Present(1);
}