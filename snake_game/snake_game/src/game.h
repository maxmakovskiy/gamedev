#pragma once

#include "Snake.h"
#include "world.h"
#include "window.h"
#include "Textbox.h"

class Game
{
public:
	World world;
	Snake snake;
	Textbox textbox;

	Game();
	~Game() {}

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow() { return &this->window; }
	sf::Time GetElapsedTime() const { this->elapsedTime; }

	void RestartClock();

private:
	Window window;

	sf::Clock clock;
	sf::Time elapsedTime;

};