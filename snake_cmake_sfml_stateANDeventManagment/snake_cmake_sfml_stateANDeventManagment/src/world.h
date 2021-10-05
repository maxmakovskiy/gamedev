#pragma once

#include "Snake.h"

class World
{
public:
	World(sf::Vector2u windowSize);
	~World() {}

	inline int GetBlockSize() const { return this->blockSize; }

	void RespawnApple();

	void Update(Snake& player);
	void Render(sf::RenderWindow& window);

private:
	sf::Vector2u windowSize;
	sf::Vector2i appleCoordinates;
	int blockSize; // represent size of one grapthic's block in the grid

	// circle for apple graphic
	sf::CircleShape appleShape;

	// 4 rectangles for boundary graphics
	sf::RectangleShape bounds[4];

};
