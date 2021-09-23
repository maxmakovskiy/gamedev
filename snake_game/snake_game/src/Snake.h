#pragma once

#include <SFML/Graphics.hpp>

// shortcut jush like define but more safe
using SnakeContainer = std::vector<SnakeSegment>;

struct SnakeSegment
{
	// position of the segment on the grid
	sf::Vector2i position;

	SnakeSegment(int x, int y) : position(x, y) {}
};

enum class Direction
{
	None = 0,
	Up,
	Down,
	Left,
	Right
};

class Snake
{
public:
	Snake(int blockSize);
	~Snake();

	// helper methods
	// Setters:
	void IncreaseScore();
	void SetDirection(Direction obj);
	// Getters:
	Direction GetDirection() const;
	int GetSpeed() const;
	sf::Vector2i GetPosition() const;
	int GetLives() const;
	int GetScore() const;
	bool IsLost() const;
	
	void Lose(); // lose control is happening here
	void ToggleLost();

	void Extend(); // grow the snake
	void Reset();  // put snake on starting position

	void Move(); // move sprites
	void Tick(); // update method
	void Cut(int segments); // method for cutting snake after head of snake touch own body or walls

	void Render(sf::RenderWindow& window);

private:
	SnakeContainer snakeBody;	// vector of snake's segments that represents whole snake body
	Direction currentDirection; // current direction of snake moving
	int snakeSpeed;				// current snake speed
	int snakeLives;				// current snake lives
	int playerScore;			// current player score
	bool lost;					// current state of losing 
	int oneRectSize;			// size of one graphic rectangle that represents one Snake Segment
	sf::RectangleShape bodyRect;// whole shape that will be using for rendering the snake

	void CheckCollision();

};

