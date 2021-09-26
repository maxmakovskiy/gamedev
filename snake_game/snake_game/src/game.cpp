#include "game.h"

Game::Game() 
	: window("Snake", sf::Vector2u(800, 600))
	, snake(this->world.GetBlockSize())
	, world(sf::Vector2u(800, 600)) 
{ 
}

void Game::HandleInput()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		&& (this->snake.GetDirection() != Direction::Down))
	{
		this->snake.SetDirection(Direction::Up);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		&& (this->snake.GetDirection() != Direction::Up))
	{
		this->snake.SetDirection(Direction::Down);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		&& (this->snake.GetDirection() != Direction::Left))
	{
		this->snake.SetDirection(Direction::Right);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		&& (this->snake.GetDirection() != Direction::Right))
	{
		this->snake.SetDirection(Direction::Left);
	}

}

void Game::Update()
{
	this->window.Update();
	textbox.Add("player's lives: " + std::to_string(snake.GetLives()));
	textbox.Add("player's score: " + std::to_string(snake.GetScore()));

	// fixed time step
	// determine amount of time for one frame
	float timeStep = 1.0f / this->snake.GetSpeed();
	float temp = this->elapsedTime.asSeconds();
	if (temp >= timeStep)
	{
		this->snake.Tick();
		this->world.Update(this->snake);
		this->elapsedTime -= sf::seconds(timeStep);

		if (this->snake.IsLost())
		{
			//textbox.Clear();
			//textbox.Add("GAME OVER!\nYour score" + std::to_string(snake.GetScore()));
			this->snake.Reset();
		}

	}

}

void Game::Render()
{
	this->window.BeginDraw();
	this->snake.Render(*(this->window.GetRenderWindow()));
	this->world.Render(*(this->window.GetRenderWindow()));
	this->textbox.Render(*(this->window.GetRenderWindow()));
	this->window.EndDraw();
}

void Game::RestartClock()
{
	this->elapsedTime += this->clock.restart();
}
