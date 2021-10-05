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
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			focused = false;
			eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			focused = true;
			eventManager.SetFocus(true);
		}

		eventManager.HandleEvent(event);
	}

	eventManager.Update();
}

void Window::ToggleFullscreen(EventDetails* details)
{
	// invert boolean flag
	this->fullscreen = !this->fullscreen;

	// destroy current window and re-created this by using new value of _isFullscreen flag
	this->Destroy();
	this->Create();
}

void Window::Draw(sf::Drawable& drawable)
{
	this->window.draw(drawable);
}

void Window::Setup(const char* title, const sf::Vector2u& size)
{
	focused = true; // window in focus by default
	eventManager.AddCallback(StateType(0), "Fullscreen_toggle", &Window::ToggleFullscreen, this);
	eventManager.AddCallback(StateType(0), "Window_close", &Window::Close, this);

	this->windowTitle = title;
	this->windowSize = size;
	this->fullscreen = false;
	this->done = false;
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
	sf::Uint32 style = this->fullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	// create window using information that stores in class members
	this->window.create(sf::VideoMode(this->windowSize.x, this->windowSize.y, 32), this->windowTitle, style);
}
