#pragma once
#include "BaseState.h"
#include "Snake.h"
#include "world.h"
#include "Textbox.h"
#include "EventManager.h"

class GameState : public BaseState
{
public:
	GameState(StateManager* stateManager)
		: BaseState(stateManager)
		, snake(world.GetBlockSize())
		, world(sf::Vector2u(800, 600))
	{}

	// callbacks for switching to the pause state and menu state
	void MainMenu(EventDetails* details);
	void Pause(EventDetails* details);
	void ArrowLeft(EventDetails* details);
	void ArrowRight(EventDetails* details);
	void ArrowUp(EventDetails* details);
	void ArrowDown(EventDetails* details);
	
	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(sf::Time& time);
	void Draw();

private:
	World world;
	Snake snake;
	Textbox textbox;

};