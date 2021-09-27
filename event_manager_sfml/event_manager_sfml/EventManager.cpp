#include "EventManager.h"

EventManager::EventManager()
	: focus(true)
{
	LoadBinding();
}

EventManager::~EventManager()
{
	for (auto& itr : bindings)
	{
		// LoadBinding allocates bindins on the heap
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding* binding)
{
	// if container has binding with the same name
	if (bindings.find(binding->name) != bindings.end())
	{
		return false;
	}
	
	return bindings.emplace(binding->name, binding).second;
}

bool EventManager::RemoveBinding(std::string name)
{
	auto itr = bindings.find(name);

	// if container is empty
	if (itr == bindings.end()) 
	{
		return false;
	}

	delete itr->second;
	bindings.erase(itr);
	return true;
}

void EventManager::HandleEvent(sf::Event& event)
{
	for (auto& bindItr : bindings)
	{
		Binding* bnd = bindItr.second;
		for (auto& eventItr : bnd->events)
		{
			EventType sfmlEvent = (EventType)event.type;
			
			if (eventItr.first != sfmlEvent)
			{
				continue;
			}

			// Store relevant event information in the EventDetails structure of the binding
			if (sfmlEvent == EventType::KeyDown ||
				sfmlEvent == EventType::KeyUp)
			{
				if (eventItr.second.code == event.key.code)
				{
					if (bnd->details.keyCode != -1)
						bnd->details.keyCode = eventItr.second.code;

					bnd->counter++;
					break;
				}
			}
			else if (sfmlEvent == EventType::MouseButtonPressed ||
				sfmlEvent == EventType::MouseButtonUp)
			{
				if (eventItr.second.code == event.mouseButton.button)
				{
					bnd->details.mouse.x = event.mouseButton.x;
					bnd->details.mouse.y = event.mouseButton.y;

					if (bnd->details.keyCode != -1)
						bnd->details.keyCode = eventItr.second.code;

					bnd->counter++;
					break;
				}
			}
			else
			{
				if (sfmlEvent == EventType::MouseWheel)
					bnd->details.mouseWheelDelta = event.mouseWheel.delta;
				else if (sfmlEvent == EventType::WindowResized)
				{
					bnd->details.size.x = event.size.width;
					bnd->details.size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered)
					bnd->details.enteredText = event.text.unicode;
				
				bnd->counter++;
			}

		}

	}
}

void EventManager::Update()
{
	// if window doesn't in focus skip this
	if (!focus) return;

	for (auto& bindItr : bindings)
	{
		Binding* bind = bindItr.second;
		for (auto& eventItr : bind->events)
		{
			// for real-time input processing we only interested in Keyboard, Mouse, Joystick devices
			switch (eventItr.first)
			{
			case EventType::Keyboard:
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eventItr.second.code)))
				{

					if (bind->details.keyCode != -1)
						bind->details.keyCode = eventItr.second.code;
					
					// incresing counter for registering match
					bind->counter++;
				}
			} break;
			case EventType::Mouse:
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eventItr.second.code)))
				{
					if (bind->details.keyCode != -1)
						bind->details.keyCode = eventItr.second.code;

					bind->counter++;
				}
			} break;
			case EventType::Joystick:
				// nothing
				break;
			}

			if (bind->events.size() == bind->counter)
			{
				auto callItr = callbacks.find(bind->name);
				if (callItr != callbacks.end())
					callItr->second(&bind->details);

			}

			bind->counter = 0;
			bind->details.Clear();
		}

	}

}

void EventManager::LoadBinding()
{
	std::string delimiter = ":";

	std::ifstream ifbindings;
	ifbindings.open("keys.cfg");
	if (!ifbindings.is_open())
	{
		std::cout << "Could not open key.cfg file!" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(ifbindings, line))
	{
		// let's parse string like Window_close 0:0
		// where "Window_close" is callback's name
		// (first)0 - type of event
		// : - delimiter
		// (second)0 - code

		std::stringstream keystream(line);
		std::string callbackName;
		
		// operator >> uses white spaces as delimiters by default
		keystream >> callbackName;

		Binding* bind = new Binding(callbackName);

		while (!keystream.eof())
		{
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			
			// if this string invalide that delete its binding
			if (end == std::string::npos)
			{
				delete bind;
				bind = nullptr;
				break;
			}
		
			//
			EventType type = EventType(std::stoi(keyval.substr(start, end - start)));

			int code = stoi(
				keyval.substr(end + delimiter.length(), 
					keyval.find(delimiter, end + delimiter.length())));

			EventInfo info;
			info.code = code;

			bind->BindEvent(type, info);
		}

		// Attempt to add bind to EventManager
		// if it operation fails
		// than delete constructed bind
		if (!AddBinding(bind))
		{
			delete bind;
		}
		
		// clear pointer to bind
		bind = nullptr;
	}
	
	// close opened resources
	ifbindings.close();

}

void SetFocus(const bool& focus);

