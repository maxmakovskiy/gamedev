#pragma once
#include "BaseState.h"
#include "EventManager.h"

class IntroState : public BaseState
{
public:
	IntroState(StateManager* stateManager)
		: BaseState(stateManager)
	{}

	~IntroState() 
	{}

	void Continue(EventDetails* details);

	void OnCreate();
	void OnDestroy();

	void Activate() {}
	void Deactivate() {}

	void Update(const sf::Time& time);
	void Draw();

private:
	sf::Texture introTexture;
	sf::Sprite introSprite;
	sf::Text textContinueMessage;
	sf::Text textWelcomeMessage;
	sf::Font font;
	float timePassed;
};