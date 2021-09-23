#pragma once

#include <SFML/Graphics.hpp>

struct SnakeSegment
{
	// position of the segment on the grid
	sf::Vector2i position;

	SnakeSegment(int x, int y) : position(x, y) {}
};

// shortcut jush like define but more safe
using SnakeContainer = std::vector<SnakeSegment>;

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
	~Snake() {}

	// helper methods
	// Setters:
	inline void IncreaseScore() { this->playerScore += 10; }
	inline void SetDirection(Direction _direction) { this->currentDirection = _direction; }
	// Getters:
	inline Direction GetDirection() const { return this->currentDirection; }
	inline int GetSpeed() const { return this->snakeSpeed; }
	sf::Vector2i GetPositionOfSnakeHead() const 
		{ return (this->snakeBody.empty() ? sf::Vector2i(1, 1) : this->snakeBody.front().position);	}
	inline int GetLives() const { return this->playerLives; }
	inline int GetScore() const { return this->playerScore; }
	inline bool IsLost() const { return this->lost; }
	
	// lose control is happening here
	inline void Lose() { this->lost = true; }
	void ToggleLost() { this->lost = !this->lost; }

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
	int playerLives;				// current snake lives
	int playerScore;			// current player score
	bool lost;					// current state of losing 
	int oneRectSize;			// size of one graphic rectangle that represents one Snake Segment
	sf::RectangleShape bodyRect;// whole shape that will be using for rendering the snake

	void CheckCollision();

};

