#pragma once
#include <SFML/Graphics.hpp>
#include "EventManager.h"


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
	void ToggleFullscreen(EventDetails* details);

	// draws passed object
	void Draw(sf::Drawable& drawable);

	void Close(EventDetails* details = nullptr) { done = true; }

	// methods for retrieving infomation about window
	// without giving too match control to outside of this class
	inline bool IsDone() { return done; }
	bool IsFullscreen() { return fullscreen; }
	bool IsFocus() { return focused; }
	sf::Vector2u GetWindowSize() { return windowSize; }

	inline EventManager* GetEventManager() { return &eventManager; }

private:
	EventManager eventManager;
	sf::RenderWindow window;
	sf::Vector2u windowSize;
	const char* windowTitle;
	bool done;
	bool fullscreen;
	bool focused;

	// helper methods for hide internall realization of window
	void Setup(const char* title, const sf::Vector2u& size);
	void Destroy();
	void Create();
};
