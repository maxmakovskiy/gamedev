#include "world.h"

World::World(sf::Vector2u windowSize)
{
	const char* pathToTexture = "F:\\gamedev\\snake_cmake_sfml_stateANDeventManagment\\snake_cmake_sfml_stateANDeventManagment\\src\\gameBackground2_800x600.png";
	backgroundTexture.loadFromFile(pathToTexture);
	backgroundSprite.setTexture(backgroundTexture);

	blockSize = 16;
	this->windowSize = windowSize;

	RespawnApple();
	appleShape.setFillColor(sf::Color::Red);
	appleShape.setRadius(blockSize / 2);
}

void World::RespawnApple()
{
	// get number of spaces in the grid between 2 walls
	int maxX = (windowSize.x / blockSize) - 2;
	int maxY = (windowSize.y / blockSize) - 2;

	// generate random values for apple's coordinates
	appleCoordinates = sf::Vector2i(
		rand() % maxX + 1,
		rand() % maxY + 1
	);

	// set position of graphics which determines apple on the board
	appleShape.setPosition(
		appleCoordinates.x * blockSize,	
		appleCoordinates.y * blockSize
	);
}

void World::Update(Snake& player)
{
	// if player's snake eats apple
	if (player.GetPositionOfSnakeHead() == appleCoordinates)
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
		player.DecreaseLives();
		
		if (player.GetLives() == 0)
			player.Lose();
	
		player.RespawnToStart();
	}
}

void World::Render(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);
	window.draw(this->appleShape);
}


