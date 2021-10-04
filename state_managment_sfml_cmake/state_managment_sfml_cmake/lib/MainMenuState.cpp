#include "MainMenuState.h"
#include "../include/StateManager.h"

void MainMenuState::OnCreate()
{
	const char* pathToTexture = "F:\\gamedev\\state_managment_sfml_cmake\\state_managment_sfml_cmake\\resources\\mainMenuBackground.png";
	if (!backgroundTexture.loadFromFile(pathToTexture))
	{
		std::cout << "Could not to load texture by given path " << pathToTexture << std::endl;
	}
	backgroundSprite.setTexture(backgroundTexture);


	const char* pathToFont = "F:\\gamedev\\state_managment_sfml_cmake\\state_managment_sfml_cmake\\resources\\arial.ttf";
	if (!font.loadFromFile(pathToFont))
		std::cout << "Failed to load font from path: " << pathToFont << std::endl;
	
	text.setFont(font);
	text.setString("Main Menu:");
	text.setCharacterSize(36);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2,
		textRect.top + textRect.top / 2);
	
	text.setPosition(400, 100);

	buttonSize = sf::Vector2f(300, 64);
	startingButtonPosition = sf::Vector2f(400, 200);
	buttonPadding = 8; // in pixels

	std::string strLabels[3];
	strLabels[0] = "PLAY";
	strLabels[1] = "CREDITS";
	strLabels[2] = "EXIT";

	// set menu buttons
	for (int i = 0; i < 3; i++)
	{
		sf::Vector2f buttonPositionI(startingButtonPosition.x,
			(startingButtonPosition.y + i * (buttonSize.y + buttonPadding)));

		buttonRects[i].setSize(buttonSize);
		buttonRects[i].setFillColor(sf::Color::Red);
		buttonRects[i].setOrigin(buttonSize.x / 2,
			buttonSize.y / 2);
		buttonRects[i].setPosition(buttonPositionI);

		buttonLabels[i].setFont(font);
		buttonLabels[i].setString(strLabels[i]);
		buttonLabels[i].setCharacterSize(18);

		sf::FloatRect buttonRectI = buttonLabels[i].getLocalBounds();
		buttonLabels[i].setOrigin(buttonRectI.left + buttonRectI.width / 2,
			buttonRectI.top + buttonRectI.height / 2);

		buttonLabels[i].setPosition(buttonPositionI);

	}

	EventManager* manager = stateManager->GetContext()->eventManager;
	manager->AddCallback(StateType::MainMenu, "Mouse_Left",
		&MainMenuState::MouseClick, this);
	manager->AddCallback(StateType::MainMenu, "Mouse_Moved",
		&MainMenuState::MouseMoved, this);
}

void MainMenuState::OnDestroy()
{
	EventManager* manager = stateManager->GetContext()->eventManager;
	manager->RemoveCallback(StateType::MainMenu, "Mouse_Left");
	manager->RemoveCallback(StateType::MainMenu, "Mouse_Moved");
}

void MainMenuState::Activate()
{
	// if we already been in game but go to the Main Menu
	// we need to see RESUME button instead of PLAY button
	if (stateManager->HasState(StateType::Game) &&
		buttonLabels[0].getString() == "PLAY")
	{
		buttonLabels[0].setString("RESUME"); 
		// after change text source we need to recompute origins
		sf::FloatRect tempRect = buttonLabels[0].getLocalBounds();
		buttonLabels[0].setOrigin(tempRect.left + tempRect.width / 2,
			tempRect.top + tempRect.height / 2);
	}
}

void MainMenuState::MouseClick(EventDetails* details)
{
	sf::Vector2i mousePosition = details->mouse;

	float halfX = buttonSize.x / 2;
	float halfY = buttonSize.y / 2;

	for (int i = 0; i < 3; i++)
	{
		// check boundaries of the buttons
		if (mousePosition.x >= buttonRects[i].getPosition().x - halfX &&
			mousePosition.x <= buttonRects[i].getPosition().x + halfX &&
			mousePosition.y >= buttonRects[i].getPosition().y - halfY &&
			mousePosition.y <= buttonRects[i].getPosition().y + halfY)
		{
			if (i == 0)
				stateManager->SwitchTo(StateType::Game);
			else if (i == 1)
			{
			//switch to credits state
			}
			else if (i == 2)
				stateManager->GetContext()->window->Close();
		}
	}

}

void MainMenuState::MouseMoved(EventDetails* details)
{
	sf::Vector2i mousePosition = details->mouse;

	float halfX = buttonSize.x / 2;
	float halfY = buttonSize.y / 2;

	for (int i = 0; i < 3; i++)
	{
		if (mousePosition.x >= buttonRects[i].getPosition().x - halfX &&
			mousePosition.x <= buttonRects[i].getPosition().x + halfX &&
			mousePosition.y >= buttonRects[i].getPosition().y - halfY &&
			mousePosition.y <= buttonRects[i].getPosition().y + halfY)
		{
			buttonRects[i].setFillColor(sf::Color::White);
			buttonLabels[i].setColor(sf::Color::Red);
		}
		else
		{
			buttonRects[i].setFillColor(sf::Color::Red);
			buttonLabels[i].setColor(sf::Color::White);
		}
	}

}

void MainMenuState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();

	window->draw(backgroundSprite);

	window->draw(text);

	for (int i = 0; i < 3; i++)
	{
		window->draw(buttonRects[i]);
		window->draw(buttonLabels[i]);
	}
}

void MainMenuState::Deactivate() 
{}

void MainMenuState::Update(const sf::Time& time)
{}




