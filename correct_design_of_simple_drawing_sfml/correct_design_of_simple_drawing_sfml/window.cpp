#include "window.h"

Window::Window()
{
	this->Setup("Window", sf::Vector2u(720, 480));
}

Window::Window(const char* title, const sf::Vector2u& size)
{
	this->Setup(title, size);
}

Window::~Window()
{
	this->Destroy();
}

void Window::BeginDraw()
{
	this->window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	this->window.display();
}

void Window::Update()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		// tracking if user press close button
		// or user press F5 for toogle between regular and fullscreen modes
		if (event.type == sf::Event::Closed)
			this->_isDone = true; 
		else if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::F5)
			ToogleFullscreen();
	}
}

void Window::ToogleFullscreen()
{
	// invert boolean flag
	this->_isFullscreen = !this->_isFullscreen;

	// destroy current window and re-created this by using new value of _isFullscreen flag
	this->Destroy();
	this->Create();
}

void Window::Draw(sf::Drawable& drawable)
{
	this->window.draw(drawable);
}

inline bool Window::IsDone()
{
	return this->_isDone;
}

inline bool Window::IsFullscreen()
{
	return this->_isFullscreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return this->windowSize;
}

void Window::Setup(const char* title, const sf::Vector2u& size)
{
	this->windowTitle = title;
	this->windowSize = size;
	this->_isFullscreen = false;
	this->_isDone = false;
	this->Create();
}

void Window::Destroy()
{
	// simply close window using RenderWindow::close() method
	this->window.close();
}

void Window::Create()
{
	// choose style of window by _isFullscreen class member
	sf::Uint32 style = this->_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	// create window using information that stores in class members
	this->window.create(sf::VideoMode(this->windowSize.x, this->windowSize.y, 32), this->windowTitle, style);
}
