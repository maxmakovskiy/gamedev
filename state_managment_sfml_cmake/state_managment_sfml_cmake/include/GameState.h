#pragma once
#include "BaseState.h"
#include "EventManager.h"

class GameState : public BaseState
{
public:
	GameState(StateManager* stateManager)
		: BaseState(stateManager)
	{}

	// callbacks for switching to the pause state and menu state
	void MainMenu(EventDetails* details);
	void Pause(EventDetails* details);
	
	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

private:
	sf::Texture ballTexture;
	sf::Sprite ballSprite;
	sf::Vector2f ballSpeed;

};

