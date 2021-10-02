#pragma once

#include "window.h"
#include "EventManager.h"
#include "StateManager.h"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();
	sf::Time GetElaped();


	void LateUpdate();
private:
	void RestartClock();

	Window window;
	StateManager stateManager;
	SharedContext sharedContext;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f speed;

	sf::Clock clock;
	sf::Time elapsed;
};
