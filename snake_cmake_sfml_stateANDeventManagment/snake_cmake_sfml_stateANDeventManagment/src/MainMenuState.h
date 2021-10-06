#pragma once

#include "BaseState.h"
#include "EventManager.h"
#include <string>

class MainMenuState : public BaseState
{
public:
	MainMenuState(StateManager* stateManager)
		: BaseState(stateManager)
	{
	}

	void MouseClick(EventDetails* details);

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(sf::Time& time);
	void Draw();

private:
	sf::Texture backTexture;
	sf::Sprite backSprite;
	sf::Text menuTitle;
	sf::Text buttonLabels[3];
	sf::Font font;
	sf::Vector2f buttonSize;
	sf::Vector2f startingButtonPosition;
	const int BUTTON_PADDING = 4;
	sf::RectangleShape buttons[3];
	std::string strLabels[3] = { "Play", "Score", "Exit" };
};
