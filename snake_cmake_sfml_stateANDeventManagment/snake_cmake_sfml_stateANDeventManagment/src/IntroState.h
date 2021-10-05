#pragma once
#include "BaseState.h"


class IntroState : public BaseState
{
public:
	IntroState(StateManager* stateManager)
		: BaseState(stateManager)
	{
	}

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Text welcomeText;
	sf::Font font;
	float timePassed;

};





