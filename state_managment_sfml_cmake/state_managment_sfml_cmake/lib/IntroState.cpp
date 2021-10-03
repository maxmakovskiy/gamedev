#include "../include/IntroState.h"
#include "../include/StateManager.h"

void IntroState::OnCreate()
{
	timePassed = 0.f;

	sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();

	const char* pathToTexture = "F:\\gamedev\\state_managment_sfml_cmake\\state_managment_sfml_cmake\\resources\\introBackground.png";
	introTexture.loadFromFile(pathToTexture);
	introSprite.setTexture(introTexture);
	
	const char* pathToFont = "F:\\gamedev\\state_managment_sfml_cmake\\state_managment_sfml_cmake\\resources\\arial.ttf";
	font.loadFromFile(pathToFont);
	textContinueMessage.setFont(font);
	textWelcomeMessage.setFont(font);

	textWelcomeMessage.setString("Welcome to the IntroState");
	textWelcomeMessage.setCharacterSize(36);
	textWelcomeMessage.setOutlineThickness(0.1);
	textWelcomeMessage.setColor(sf::Color(28, 28, 28));

	textContinueMessage.setString("Press SPACE to continue");
	textContinueMessage.setCharacterSize(24);
	textContinueMessage.setOutlineThickness(0.2);
	textContinueMessage.setColor(sf::Color::White);

	sf::FloatRect textRect = textContinueMessage.getLocalBounds();
	textContinueMessage.setOrigin(textRect.left + textRect.width / 2,
				   textRect.top + textRect.height / 2);
	textContinueMessage.setPosition(windowSize.x / 2, windowSize.y / 2);

	textRect = textWelcomeMessage.getLocalBounds();
	textWelcomeMessage.setOrigin(textRect.left + textRect.width / 2,
				   textRect.top + textRect.height / 2);
	textWelcomeMessage.setPosition(windowSize.x / 2, 100);

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
	// throughout 3 seconds
	if (timePassed < 3.f) // less than 3 seconds
	{
		timePassed += time.asSeconds();

		return;
	}
	introSprite.setColor(sf::Color(128,128,128,255));
}

void IntroState::Continue(EventDetails* details)
{
	// if enough time has passed to continue past this state
	if (timePassed >= 3.f)
	{
		stateManager->SwitchTo(StateType::MainMenu);
		stateManager->Remove(StateType::Intro);
	}
}

void IntroState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();
	window->draw(introSprite);

	// if 3 seconds passed
	if (timePassed >= 3.f)
	{
		window->draw(textContinueMessage);
	}
	else
	{
		window->draw(textWelcomeMessage);
	}
}

