#include "GameState.h"
#include "StateManager.h"

void GameState::MainMenu(EventDetails* details) 
{
	stateManager->SwitchTo(StateType::MainMenu);
}

void GameState::Pause(EventDetails* details) 
{
	stateManager->SwitchTo(StateType::Paused);
}

void GameState::ArrowLeft(EventDetails* details)
{
	if (snake.GetDirection() != Direction::Right)
		snake.SetDirection(Direction::Left);
}

void GameState::ArrowRight(EventDetails* details) 
{
	if (snake.GetDirection() != Direction::Left)
		snake.SetDirection(Direction::Right);
}

void GameState::ArrowUp(EventDetails* details) 
{
	if (snake.GetDirection() != Direction::Down)
		snake.SetDirection(Direction::Up);
}

void GameState::ArrowDown(EventDetails* details) 
{
	if (snake.GetDirection() != Direction::Up)
		snake.SetDirection(Direction::Down);
}

void GameState::OnCreate() 
{
	EventManager* manager = stateManager->GetContext()->eventManager;
	manager->AddCallback(StateType::Game, "Key_Escape", &GameState::MainMenu, this);
	manager->AddCallback(StateType::Game, "Key_P", &GameState::Pause, this);
	manager->AddCallback(StateType::Game, "Key_ArrowUp", &GameState::ArrowUp, this);
	manager->AddCallback(StateType::Game, "Key_ArrowDown", &GameState::ArrowDown, this);
	manager->AddCallback(StateType::Game, "Key_ArrowRight", &GameState::ArrowRight, this);
	manager->AddCallback(StateType::Game, "Key_ArrowLeft", &GameState::ArrowLeft, this);

}

void GameState::OnDestroy() 
{
	EventManager* manager = stateManager->GetContext()->eventManager;
	manager->RemoveCallback(StateType::MainMenu, "Key_Escape");
	manager->RemoveCallback(StateType::Paused, "Key_P");
	manager->RemoveCallback(StateType::Game, "Key_ArrowUp");
	manager->RemoveCallback(StateType::Game, "Key_ArrowDown");
	manager->RemoveCallback(StateType::Game, "Key_ArrowRight");
	manager->RemoveCallback(StateType::Game, "Key_ArrowLeft");

}

void GameState::Activate() 
{
}

void GameState::Deactivate() 
{
	snake.SetDirection(Direction::None);
}

void GameState::Update(sf::Time& time) 
{
	textbox.Add("player's lives: " + std::to_string(snake.GetLives()));
	textbox.Add("player's score: " + std::to_string(snake.GetScore()));

	// fixed time step
	// determine amount of time for one frame
	float timeStep = 1.0f / snake.GetSpeed();
	float temp = time.asSeconds();
	if (temp >= timeStep)
	{
		snake.Tick();
		world.Update(snake);
		time -= sf::seconds(timeStep);

		if (snake.IsLost())
		{
			snake.Reset();
		}

	}

}

void GameState::Draw() 
{
	sf::RenderWindow* wind = stateManager->GetContext()->window->GetRenderWindow();
	world.Render(*wind);
	snake.Render(*wind);
	textbox.Render(*wind);
}


