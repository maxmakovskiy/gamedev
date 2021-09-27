#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

// All type of events
enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MouseButtonPressed = sf::Event::MouseButtonPressed,
	MouseButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1,
	Mouse = sf::Event::Count + 2,
	Joystick = sf::Event::Count + 3
};

// Data type for defining information(code) about event
struct EventInfo
{
	union
	{
		int eventCode;
	};

	// this constructor needed for events which only need type of event
	EventInfo()
	{
		eventCode = 0;
	}

	EventInfo(int code)
	{
		eventCode = code;
	}
};

// alies for convenient store events info
using Events = std::vector<std::pair<EventType, EventInfo>>;

// Data type for share event info with code that uses this class
struct EventDetails
{
	std::string name;
	sf::Vector2i size;
	sf::Uint32 enteredText;
	sf::Vector2i mouse;
	int mouseWheelDelta;
	int keyCode; // single key code

	EventDetails(const std::string& bindName)
		: name(bindName)
	{
		Clear();
	}

	void Clear()
	{
		size = sf::Vector2i(0, 0);
		enteredText = 0;
		mouse = sf::Vector2i(0, 0);
		mouseWheelDelta = 0;
		keyCode = -1;
	}
};

// Data type for holding all the event information
struct Binding
{
	Events events;
	std::string name;
	int counter; // count of events that are happening
	EventDetails details;

	Binding(const std::string& name)
		: name(name)
		, details(name)
		, counter(0) 
	{}

	void BindEvent(EventType type, EventInfo info = EventInfo())
	{
		events.emplace_back(type, info);
	}

};

// alias for storing unique bindings and store action name as key string 
using Bindings = std::unordered_map<std::string, Binding*>;










