#pragma once
#include <SFML/Graphics.hpp>


class Window
{
public:
	// default constructor
	Window();

	// Construct a new window by given title and size
	Window(const char* title, const sf::Vector2u& size);

	// Close window and frees all its resource
	~Window();

	// clear the window
	void BeginDraw();

	// display the changes
	void EndDraw();

	// method for processing events of window
	void Update();

	// helps to toogle between regular and fullscreen modes
	void ToogleFullscreen();

	// draws passed object
	void Draw(sf::Drawable& drawable);

	// methods for retrieving infomation about window
	// without giving too match control to outside of this class
	inline bool IsDone();
	inline bool IsFullscreen();
	sf::Vector2u GetWindowSize();

private:
	sf::RenderWindow window;
	sf::Vector2u windowSize;
	const char* windowTitle;
	bool _isDone;
	bool _isFullscreen;

	// helper methods for hide internall realization of window
	void Setup(const char* title, const sf::Vector2u& size);
	void Destroy();
	void Create();
};
