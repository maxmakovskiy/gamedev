#pragma once

#include "window.h"
#include "EventManager.h"

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
	void RestartClock();
private:
	void MoveSprite(EventDetails* details = nullptr);

	Window window;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f speed;

	sf::Clock clock;
	sf::Time elapsed;
};
