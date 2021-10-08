#include "game.h"

Game::Game()
	: window("Snake Game", sf::Vector2u(800, 600))
	, stateManager(&sharedContext)
{
	// setup context
	sharedContext.window = &window;
	sharedContext.eventManager = window.GetEventManager();

	stateManager.SwitchTo(StateType::Intro);

}

Game::~Game() {}

void Game::HandleInput() {}

void Game::Update()
{
	window.Update(); // update window events
	stateManager.Update(deltaTime, elapsedTime);
}

void Game::Render()
{
	window.BeginDraw(); // clear
	stateManager.Draw();	
	window.EndDraw(); // display
}

void Game::LateUpdate()
{
	stateManager.ProcessRequests();
	RestartClock();
}

void Game::RestartClock()
{
	deltaTime += deltaClock.restart();
	elapsedTime = elapsedClock.restart();
}