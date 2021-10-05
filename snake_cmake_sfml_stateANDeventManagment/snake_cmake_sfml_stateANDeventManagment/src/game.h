#pragma once

#include "Snake.h"
#include "world.h"
#include "window.h"
#include "Textbox.h"
#include "StateManager.h"
#include "EventManager.h"


class Game
{
public:
	//World world;
	//Snake snake;
	//Textbox textbox;

	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow() { return &this->window; }
	sf::Time GetElapsed() const { this->elapsedTime; }

	void LateUpdate();

private:
	Window window;
	StateManager stateManager;
	SharedContext sharedContext;
	sf::Clock clock;
	sf::Time elapsedTime;

	void RestartClock();
};