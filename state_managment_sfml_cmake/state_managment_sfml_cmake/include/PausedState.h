#pragma once
#include "BaseState.h"
#include "EventManager.h"

class PausedState : public BaseState
{
public:
	PausedState(StateManager* stateManager)
		: BaseState(stateManager)
	{}

	void Unpaused(EventDetails* details);

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();
	
private:
	sf::Text text;
	sf::Font font;
	sf::RectangleShape rectDarker;
};

