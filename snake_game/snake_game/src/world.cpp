#include "world.h"

World::World(sf::Vector2u windowSize)
{
	this->blockSize = 16;
	this->windowSize = windowSize;

	this->RespawnApple();
	this->appleShape.setFillColor(sf::Color::Red);
	this->appleShape.setRadius(this->blockSize / 2);

	// setup walls
	for (int i = 0; i < 4; i++)
	{
		this->bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 4) % 2)) // divide to 2 vertical sides and 2 horizontal sides
		{
			this->bounds[i].setSize(sf::Vector2f(windowSize.x, blockSize));
		}
		else
		{
			this->bounds[i].setSize(sf::Vector2f(blockSize, windowSize.y));
		}

		if (i < 2) // if we are working with left-upper corner
			// don't need to change origin of rectangle because it's in top-left rectangle's corner by default
			// jush change its position to upper-left window's corner
			this->bounds[i].setPosition(0, 0);
		else
		{
			// change origin of rectangle to bottom-right rectangle's corner
			this->bounds[i].setOrigin(this->bounds[i].getSize());
			// and change its position to window's lower-left corner
			this->bounds[i].setPosition(sf::Vector2f(this->windowSize));
		}
	}
}

void World::RespawnApple()
{
	// get number of spaces in the grid between 2 walls
	int maxX = (this->windowSize.x / this->blockSize) - 2;
	int maxY = (this->windowSize.y / this->blockSize) - 2;

	// generate random values for apple's coordinates
	this->appleCoordinates = sf::Vector2i(
		rand() % maxX + 1,
		rand() % maxY + 1
	);

	// set position of graphics which determines apple on the board
	this->appleShape.setPosition(
		this->appleCoordinates.x * this->blockSize,	
		this->appleCoordinates.y * this->blockSize
	);
}

void World::Update(Snake& player)
{
	// if player's snake eats apple
	if (player.GetPositionOfSnakeHead() == this->appleCoordinates)
	{
		player.Extend();
		player.IncreaseScore();
		this->RespawnApple();
	}

	// and check if player's snake was hit in the walls
	int gridSizeX = this->windowSize.x / this->blockSize;
	int gridSizeY = this->windowSize.y / this->blockSize;
		
	if (player.GetPositionOfSnakeHead().x <= 0 ||
		player.GetPositionOfSnakeHead().y <= 0 ||
		player.GetPositionOfSnakeHead().x >= (gridSizeX - 1) ||
		player.GetPositionOfSnakeHead().y >= (gridSizeY - 1))
	{ // call Lose method for illustrate collision with wall
		player.Lose();
	}
}

void World::Render(sf::RenderWindow& window)
{
	// draw walls and apple
	for (int i = 0; i < 4; i++)
	{
		window.draw(this->bounds[i]);
	}

	window.draw(this->appleShape);
}


