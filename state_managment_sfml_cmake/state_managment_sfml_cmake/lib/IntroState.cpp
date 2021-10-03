#include "../include/IntroState.h"
#include "../include/StateManager.h"

void IntroState::OnCreate()
{
	timePassed = 0.0f;

	sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();

	const char* pathToTexture = "F:\\gamedev\\state_managment_sfml_cmake\\state_managment_sfml_cmake\\resources\\introBackground.png";
	introTexture.loadFromFile(pathToTexture);
//	introTexture.loadFromFile("..\\resources\\introBackground.png");
	introSprite.setTexture(introTexture);

	introSprite.setOrigin(introTexture.getSize().x / 2,
		introTexture.getSize().y / 2);
	introSprite.setPosition(windowSize.x / 2, 0);
	
	const char* pathToFont = "F:\\gamedev\\state_managment_sfml_cmake\\state_managment_sfml_cmake\\resources\\arial.ttf";
//	font.loadFromFile("..\\resources\\arial.ttf");
	font.loadFromFile(pathToFont);
	text.setFont(font);

	text.setString("Press SPACE to continue");
	text.setCharacterSize(24);
	text.setOutlineThickness(0.2);
	text.setColor(sf::Color(33, 33, 33));

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2,
				   textRect.top + textRect.height / 2);
	text.setPosition(windowSize.x / 2, windowSize.y / 2);

	// bind Space key to the Continue method
	EventManager* manager = stateManager->GetContext()->eventManager;
	manager->AddCallback(StateType::Intro,
						"Intro_Continue",
						&IntroState::Continue,
						this);

}

void IntroState::OnDestroy()
{
	EventManager* manager = stateManager->GetContext()->eventManager;
	manager->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void IntroState::Update(const sf::Time& time)
{
	// sprite come down from the top of the screen to the middle
	// throughout 5 seconds
	if (timePassed < 5.f) // less than 5 seconds
	{
		timePassed += time.asSeconds();
		introSprite.setPosition(
			introSprite.getPosition().x,
			introSprite.getPosition().y + (60 * time.asSeconds())
		);
	}
}

void IntroState::Continue(EventDetails* details)
{
	// if enough time has passed to continue past this state
	if (timePassed >= 5.f)
	{
		stateManager->SwitchTo(StateType::MainMenu);
		stateManager->Remove(StateType::Intro);
	}
}

void IntroState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();
	window->draw(introSprite);

	// if 5 seconds passed
	if (timePassed >= 5.f)
	{
		window->draw(text);
	}
}

