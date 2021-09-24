#pragma once

#include "Snake.h"
#include "world.h"
#include "window.h"

class Game
{
public:
	World world;
	Snake snake;

	Game();
	~Game() {}

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow() { return &this->window; }
	float GetElapsedTime() const { this->elapsedTime; }

	void RestartClock();
private:
	Window window;

	sf::Clock clock;
	float elapsedTime;

};