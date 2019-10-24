#include "PCH.h"
#include "GameStateMachine.h"

void GameStateMachine::push(std::unique_ptr<GameState> states)
{
	m_gameStates.emplace_back(std::move(states));
	//m_gameStates.push_back(std::move(states));
	m_gameStates.back()->on_enter();
}

void GameStateMachine::pop()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->on_exit();
		m_gameStates.pop_back();
	}
}

void GameStateMachine::update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}
}

void GameStateMachine::render(Renderer* renderer)
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render(renderer);
	}
}

void GameStateMachine::handleEvents()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->handle_events();
	}
}

void GameStateMachine::unloadAll()
{
	while (!m_gameStates.empty())
	{
		pop();
	}
}