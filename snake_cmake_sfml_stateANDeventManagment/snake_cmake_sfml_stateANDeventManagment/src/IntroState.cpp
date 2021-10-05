#include "IntroState.h"
#include "StateManager.h"

void IntroState::OnCreate()
{
	timePassed = 0.f;

	const char* pathToTexture = "F:\\gamedev\\snake_cmake_sfml_stateANDeventManagment\\snake_cmake_sfml_stateANDeventManagment\\src\\introBackgrndSnake.png";
	backgroundTexture.loadFromFile(pathToTexture);

	backgroundSprite.setTexture(backgroundTexture);
	
	const char* pathToFont = "F:\\gamedev\\snake_cmake_sfml_stateANDeventManagment\\snake_cmake_sfml_stateANDeventManagment\\src\\arial.ttf";
	font.loadFromFile(pathToFont);
	
	welcomeText.setFont(font);
	welcomeText.setString("Welcome to the\n Snake Game");
	welcomeText.setCharacterSize(36);
	welcomeText.setStyle(sf::Text::Bold);
	welcomeText.setFillColor(sf::Color::White);

	sf::FloatRect textDimensions = welcomeText.getLocalBounds();
	welcomeText.setOrigin(textDimensions.left + textDimensions.width / 2,
		textDimensions.top + textDimensions.height / 2);
	sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();
	welcomeText.setPosition(windowSize.x / 2, windowSize.y / 2);

}

void IntroState::OnDestroy()
{}

void IntroState::Update(const sf::Time& time)
{
	if (timePassed < 3.f)
	{
		timePassed += time.asSeconds();
	}
	else
	{
		stateManager->SwitchTo(StateType::MainMenu);
	}
}

void IntroState::Draw()
{
	sf::RenderWindow* wind = stateManager->GetContext()->window->GetRenderWindow();
	wind->draw(backgroundSprite);
	wind->draw(welcomeText);
}

void IntroState::Activate() {}
void IntroState::Deactivate() {}
