#include "Snake.h"

Snake::Snake(int blockSize)
{
	this->oneRectSize = blockSize;
	this->bodyRect.setSize(sf::Vector2f(this->oneRectSize - 1, this->oneRectSize - 1));
	this->Reset();
}

void Snake::Reset()
{
	this->snakeBody.clear();

	// TEMPORARY:
	// hardcode starting snake's body with 3 segments and their positions
	this->snakeBody.push_back(SnakeSegment(5, 7));
	this->snakeBody.push_back(SnakeSegment(5, 6));
	this->snakeBody.push_back(SnakeSegment(5, 5));

	// Just define a couple of starting parameters
	this->SetDirection(Direction::None);
	this->snakeSpeed = 15; // 15 px of 1 sec
	this->playerLives = 3;  // snake has 3 lives
	this->playerScore = 0; // starting score is 0
	this->lost = false;
}

// PURPOSE:
// growing up snake when it touched to apple
void Snake::Extend()
{
	if (this->snakeBody.empty()) return;

	SnakeSegment& tailHead = this->snakeBody[this->snakeBody.size() - 1];
	if (this->snakeBody.size() > 1)
	{
		SnakeSegment& tailBone = this->snakeBody[this->snakeBody.size() - 2];
		if (tailHead.position.x == tailBone.position.x)
		{
			if (tailHead.position.y > tailBone.position.y)
				this->snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
			else 
				this->snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
		}
		else if (tailHead.position.y == tailBone.position.y)
		{
			if (tailHead.position.x > tailBone.position.x)
				this->snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
			else
				this->snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
		}
	}
	else // snake size equals to 1
	{
		if (this->currentDirection == Direction::Up)
			this->snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
		else if (this->currentDirection == Direction::Down)
			this->snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
		else if (this->currentDirection == Direction::Left)
			this->snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
		else if (this->currentDirection == Direction::Right)
			this->snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
	}

}

void Snake::Tick()
{
	// Check if snake should be moved or not
	// based on its body size and direction
	if (this->snakeBody.empty()
		|| this->currentDirection == Direction::None) return;
	
	this->Move();
	this->CheckCollision();
}

void Snake::Move()
{
	for (int i = this->snakeBody.size() - 1; i > 0; i--)
	{
		this->snakeBody[i].position = this->snakeBody[i - 1].position;
	}

	if (this->currentDirection == Direction::Up)
		this->snakeBody[0].position.y--;
	else if (this->currentDirection == Direction::Down)
		this->snakeBody[0].position.y++;
	else if (this->currentDirection == Direction::Right)
		this->snakeBody[0].position.x++;
	else if (this->currentDirection == Direction::Left)
		this->snakeBody[0].position.x--;
}

void Snake::CheckCollision()
{
	// no need to find check the collision if snake has size less then 5 segments
	if (this->snakeBody.size() < 5) return;
	
	SnakeSegment& head = this->snakeBody.front();

	for (SnakeContainer::iterator itr = this->snakeBody.begin() + 1;
		itr != this->snakeBody.end(); itr++)
	{
		// if snake's head was touched to certain body segment which determines by current position of iterator
		if (itr->position == head.position)
		{
			// subtraction between both iterators gives us the distance between them
			int segments = this->snakeBody.end() - itr;
			this->Cut(segments);
			break;
		}
	}

}

void Snake::Cut(int segments)
{
	for (int i = 0; i < segments; i++)
		this->snakeBody.pop_back();
	
	this->playerLives--;

	// If player wastes all given lives
	if (this->playerLives == 0)
		this->Lose();

}

void Snake::Render(sf::RenderWindow& window)
{
	if (this->snakeBody.empty()) return;

	SnakeContainer::iterator head = this->snakeBody.begin();
	// setup the head and draw it
	this->bodyRect.setFillColor(sf::Color::Blue);
	this->bodyRect.setPosition(
		head->position.x * this->oneRectSize,
		head->position.y * this->oneRectSize
	);
	window.draw(this->bodyRect);

	// setup the body and draw it
	this->bodyRect.setFillColor(sf::Color::White);
	// itr = head + 1 => skip the head 'cause we already processing it
	for (SnakeContainer::iterator itr = head + 1;
		itr != this->snakeBody.end(); itr++)
	{
		this->bodyRect.setPosition(
			itr->position.x * this->oneRectSize,	
			itr->position.y * this->oneRectSize
		);

		window.draw(this->bodyRect);

	}

}

void Snake::RespawnToStart()
{
	this->SetDirection(Direction::None);
	
	int initVal = snakeBody.size() - 3;
	for (int i = 0; i < initVal; i++)
	{
		snakeBody.pop_back();
	}
	
	for (int i = 0; i < snakeBody.size(); i++)
	{
		snakeBody[i].position.x = 5;
		snakeBody[i].position.y = 7 - i;
	}
}
