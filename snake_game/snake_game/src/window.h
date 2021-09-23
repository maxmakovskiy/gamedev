#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	Window(const char* title, const sf::Vector2u& size);

	~Window();

	void BeginDraw() { this->window.clear(sf::Color::Black); }
	void Draw(sf::Drawable& obj) { this->window.draw(obj); }
	void EndDraw() { this->window.display(); }

	void Update();
	void ToogleFullscreen();

	bool IsDone() { return this->done; }
	bool IsFullscreen() { return this->fullscreen; }
	sf::Vector2u GetSize() { this->size; }

private:
	sf::RenderWindow window;
	sf::Vector2u size;
	const char* title;
	bool done;
	bool fullscreen;

	void Setup(const char* title, const sf::Vector2u& size);
	void Create();
	void Destroy();
};
