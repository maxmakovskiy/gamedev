#pragma once


#include "window.h"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

private:
	void MoveSprite();

	Window window;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f speed;
};
