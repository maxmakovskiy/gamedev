#include "../include/PausedState.h"
#include "../include/StateManager.h"

void PausedState::OnCreate()
{
	// set transparent flag
	// this means we allow the StateManager to render
	// Game state behind Paused state
	SetTransparent(true);

	const char* pathToFont = "F:\\gamedev\\state_managment_sfml_cmake\\state_managment_sfml_cmake\\resources\\arial.ttf";
	if (!font.loadFromFile(pathToFont))
	{
		std::cout << "Unable to load font from " << pathToFont << std::endl;
	}
	text.setFont(font);

	text.setString("PAUSED");
	text.setCharacterSize(28);
	text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2,
		textRect.top + textRect.height / 2);
	text.setPosition(windowSize.x / 2, windowSize.y / 2);

	rectDarker.setSize(sf::Vector2f(windowSize));
	rectDarker.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager* manager = stateManager->GetContext()->eventManager;
	manager->AddCallback(StateType::Paused, "Key_P",
		&PausedState::Unpaused, this);
	
}

void PausedState::OnDestroy()
{
	stateManager->GetContext()->eventManager->RemoveCallback(StateType::Paused, "Key_P");
}

void PausedState::Draw()
{
	sf::RenderWindow* wind = stateManager->GetContext()->window->GetRenderWindow();
	wind->draw(rectDarker);
	wind->draw(text);
}

void PausedState::Unpaused(EventDetails* details)
{
	stateManager->SwitchTo(StateType::Game);
}

void PausedState::Activate()
{}

void PausedState::Deactivate()
{}

void PausedState::Update(const sf::Time& time)
{}


