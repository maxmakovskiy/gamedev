#include "window.h"

Window::Window()
{
	this->Setup("Game", sf::Vector2u(800, 600));
}

Window::Window(const char* title, const sf::Vector2u& size)
{
	this->Setup(title, size);
}

void Window::Setup(const char* title, const sf::Vector2u& size)
{
	this->title = title;
	this->size = size;
	this->done = false;
	this->fullscreen = false;
	this->Create();
}

void Window::Create()
{
	sf::Uint32 style = this->fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	this->window.create(sf::VideoMode(this->size.x, this->size.y, 32), this->title, style);
}

Window::~Window()
{
	this->Destroy();
}

void Window::Destroy()
{
	this->window.close();
}

void Window::Update()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->done = false;
		else if (event.key.code == sf::Keyboard::F5 &&
			event.type == sf::Event::KeyPressed)
			this->ToogleFullscreen();

	}
}

void Window::ToogleFullscreen()
{
	this->fullscreen = !this->fullscreen;
	
	this->Destroy();
	this->Create();
}
