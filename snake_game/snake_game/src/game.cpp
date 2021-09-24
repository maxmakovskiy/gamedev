#include "game.h"

Game::Game() 
	: window("Snake", sf::Vector2u(800, 600))
	, snake(this->world.GetBlockSize())
	, world(sf::Vector2u(800, 600)) { }

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& (this->snake.GetDirection() != Direction::Down))
	{
		this->snake.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& (this->snake.GetDirection() != Direction::Up))
	{
		this->snake.SetDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& (this->snake.GetDirection() != Direction::Left))
	{
		this->snake.SetDirection(Direction::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& (this->snake.GetDirection() != Direction::Right))
	{
		this->snake.SetDirection(Direction::Left);
	}

}

void Game::Update()
{
	this->window.Update();
	
	float timeStep = 1.0f / this->snake.GetSpeed();

	if (elapsedTime >= timeStep)
	{
		this->snake.Tick();
		this->world.Update(this->snake);
		this->elapsedTime -= timeStep;

		if (this->snake.IsLost())
		{
			this->snake.Reset();
		}

	}

}

void Game::Render()
{
	this->window.BeginDraw();
	this->snake.Render(*(this->window.GetRenderWindow()));
	this->world.Render(*(this->window.GetRenderWindow()));
	this->window.EndDraw();
}

void Game::RestartClock()
{
	this->elapsedTime = this->clock.getElapsedTime().asSeconds();
}
