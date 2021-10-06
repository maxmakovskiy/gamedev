#include "PausedState.h"
#include "StateManager.h"

void PausedState::Unpaused(EventDetails* details) 
{
	stateManager->SwitchTo(StateType::Game);
}

void PausedState::OnCreate() 
{
	SetTransparent(true);
	
	const char* pathToFont = "F:\\gamedev\\snake_cmake_sfml_stateANDeventManagment\\snake_cmake_sfml_stateANDeventManagment\\src\\arial.ttf";
	font.loadFromFile(pathToFont);
	text.setFont(font);

	text.setString("PAUSED");
	text.setCharacterSize(28);
	text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();
	sf::FloatRect textDimns = text.getLocalBounds();

	text.setOrigin(textDimns.left + textDimns.width / 2,
		textDimns.top + textDimns.height / 2);
	text.setPosition(windowSize.x / 2, windowSize.y / 2);

	rectDarker.setSize(sf::Vector2f(windowSize));
	rectDarker.setFillColor(sf::Color(0, 0, 0, 150));


	stateManager->GetContext()->eventManager->AddCallback(
		StateType::Paused, "Key_P", &PausedState::Unpaused, this);

}

void PausedState::OnDestroy() 
{
	stateManager->GetContext()->eventManager->RemoveCallback(StateType::Paused, "Key_P");
}

void PausedState::Activate() {}

void PausedState::Deactivate() {}

void PausedState::Update(sf::Time& time) {}

void PausedState::Draw() 
{
	sf::RenderWindow* wind = stateManager->GetContext()->window->GetRenderWindow();
	wind->draw(rectDarker);
	wind->draw(text);
}


