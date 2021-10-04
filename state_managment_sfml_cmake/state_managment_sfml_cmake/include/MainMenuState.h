#pragma once
#include "BaseState.h"
#include "EventManager.h"

class MainMenuState : public BaseState
{
public:
	MainMenuState(StateManager* stateManager)
		: BaseState(stateManager)
	{}

	~MainMenuState() {}

	void MouseClick(EventDetails* details);

	void OnCreate();
	void OnDestroy();

	void Activate() {}
	void Deactivate() {}

	void Update(const sf::Time& time);
	void Draw();

private:
	sf::Text text;
	sf::Vector2f buttonSize;
	sf::Vector2f buttonPosition;
	unsigned int buttonPadding;

	sf::RectangleShape buttonRects[3];
	sf::Text buttonLabels[3];

};