#include "../include/game.h"

Game::Game()
	: window("Bouncing Ball", sf::Vector2u(800, 600))
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
	stateManager.Update(elapsed);
}

void Game::Render()
{
	window.BeginDraw(); // clear
	stateManager.Draw();	
	//window.Draw(this->sprite);
	window.EndDraw(); // display
}

Window* Game::GetWindow()
{
	return &window;
}

sf::Time Game::GetElaped()
{
	return elapsed;
}

void Game::RestartClock()
{
	elapsed = clock.restart();
}

void Game::LateUpdate()
{
	stateManager.ProcessRequests();
	RestartClock();
}