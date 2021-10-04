#include "../include/GameState.h"
#include "../include/StateManager.h"

void GameState::OnCreate()
{
	const char* pathToBackground = "F:\\gamedev\\state_managment_sfml_cmake\\state_managment_sfml_cmake\\resources\\gameBackground.png";
	if (!backgroundTexture.loadFromFile(pathToBackground))
	{
		std::cout << "Unable to load ball texture by given path " << pathToBackground << std::endl;
	}
	backgroundSprite.setTexture(backgroundTexture);

	const char* pathToBall = "F:\\gamedev\\state_managment_sfml_cmake\\state_managment_sfml_cmake\\resources\\ballYellow.png";
	if (!ballTexture.loadFromFile(pathToBall))
	{
		std::cout << "Unable to load ball texture by given path " << pathToBall << std::endl;
	}
	ballSprite.setTexture(ballTexture);

	ballSprite.setOrigin(ballTexture.getSize().x / 2, ballTexture.getSize().y / 2);
	
	ballSpeed = sf::Vector2f(200, 200);

	// add callbacks for listening key pressed P - pause, ESC - go to main menu
	stateManager->GetContext()->eventManager->AddCallback(
		StateType::Game, "Key_P", &GameState::Pause, this);
	stateManager->GetContext()->eventManager->AddCallback(
		StateType::Game, "Key_Escape", &GameState::MainMenu, this);
}

void GameState::OnDestroy()
{
	stateManager->GetContext()->eventManager->RemoveCallback(StateType::Paused, "Key_P");
	stateManager->GetContext()->eventManager->RemoveCallback(StateType::MainMenu, "Key_Escape");
}

void GameState::Update(const sf::Time& time)
{
	sf::Vector2u windowSize = stateManager->GetContext()->window->GetWindowSize();
	sf::Vector2u textureSize = ballTexture.getSize();

	if((ballSprite.getPosition().x + (textureSize.x / 2) > windowSize.x && ballSpeed.x > 0) ||
		(ballSprite.getPosition().x - (textureSize.x / 2) < 0 && this->ballSpeed.x < 0))
	{
		// Reverse the direction on X axis.
		ballSpeed.x = -ballSpeed.x;
	}

	if((ballSprite.getPosition().y + (textureSize.y / 2) > windowSize.y && ballSpeed.y > 0) ||
		(ballSprite.getPosition().y - (textureSize.y / 2) < 0 && ballSpeed.y < 0))
	{
		// Reverse the direction on Y axis.
		ballSpeed.y = -ballSpeed.y;
	}

	float timeElapsed = time.asSeconds();
	ballSprite.setPosition(
		ballSprite.getPosition().x + (ballSpeed.x * timeElapsed),
		ballSprite.getPosition().y + (ballSpeed.y * timeElapsed)
	);

}

void GameState::Draw()
{
	sf::RenderWindow* wind = stateManager->GetContext()->window->GetRenderWindow();

	wind->draw(backgroundSprite);
	wind->draw(ballSprite);
}

void GameState::MainMenu(EventDetails* details)
{
	stateManager->SwitchTo(StateType::MainMenu);
}

void GameState::Pause(EventDetails* details)
{
	stateManager->SwitchTo(StateType::Paused);
}

void GameState::Activate()
{}

void GameState::Deactivate()
{}


