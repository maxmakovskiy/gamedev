#include "game.h"

Game::Game()
	: window("Bouncing Ball", sf::Vector2u(800, 600))
{
	const char* pathToFile = "F:\\gamedev\\correct_design_of_simple_drawing_sfml\\correct_design_of_simple_drawing_sfml\\ballYellow.png";
	if (!this->texture.loadFromFile(pathToFile))
	{
		fprintf(stderr, "Error occurs while load texture from file by path: %s", pathToFile);
	}
	
	this->sprite.setTexture(this->texture);
	this->speed = sf::Vector2f(200.0f, 200.0f);

	this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

}

Game::~Game() {}

void Game::HandleInput() {}

void Game::Update()
{
	this->window.Update(); // update window events
	this->MoveSprite();
}

void Game::Render()
{
	this->window.BeginDraw(); // clear
	this->window.Draw(this->sprite);
	this->window.EndDraw(); // display
}

Window* Game::GetWindow()
{
	return &this->window;
}

void Game::MoveSprite()
{
	sf::Vector2u windowSize = this->window.GetWindowSize();
	sf::Vector2u textureSize = this->texture.getSize();

	if((this->sprite.getPosition().x + (textureSize.x / 2) > windowSize.x && this->speed.x > 0) ||
		(this->sprite.getPosition().x - (textureSize.x / 2) < 0 && this->speed.x < 0))
	{
		// Reverse the direction on X axis.
		this->speed.x = -this->speed.x;
	}

	if((this->sprite.getPosition().y + (textureSize.y / 2) > windowSize.y && this->speed.y > 0) ||
		(this->sprite.getPosition().y - (textureSize.y / 2) < 0 && this->speed.y < 0))
	{
		// Reverse the direction on Y axis.
		this->speed.y = -this->speed.y;
	}

	// get time since clock was last time (re-)started
	float timeElapsed = this->elapsed.asSeconds();
	this->sprite.setPosition(
		// determine distance for ball move over one iteration
		// distance = speed(hardcoded) * time(that system consumes to make one iteration through the main game loop)
		this->sprite.getPosition().x + (this->speed.x * timeElapsed),
		this->sprite.getPosition().y + (this->speed.y * timeElapsed)
	);

}

sf::Time Game::GetElaped()
{
	return this->elapsed;
}

void Game::RestartClock()
{
	this->elapsed = this->clock.restart();
}

