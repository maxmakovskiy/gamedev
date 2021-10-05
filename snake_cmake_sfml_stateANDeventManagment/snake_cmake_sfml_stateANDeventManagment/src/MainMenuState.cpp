#include "MainMenuState.h"
#include "StateManager.h"

void MainMenuState::MouseClick(EventDetails* details)
{
	sf::Vector2i mousePosition = details->mouse;

	float halfX = buttonSize.x / 2;
	float halfY = buttonSize.y / 2;

	for (int i = 0; i < 3; i++)
	{
		// check boundaries of the buttons
		if (mousePosition.x >= buttons[i].getPosition().x - halfX &&
			mousePosition.x <= buttons[i].getPosition().x + halfX &&
			mousePosition.y >= buttons[i].getPosition().y - halfY &&
			mousePosition.y <= buttons[i].getPosition().y + halfY)
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

void MainMenuState::OnCreate()
{
	buttonSize = sf::Vector2f(300.f, 64.f);
	startingButtonPosition = sf::Vector2f(400.f, 200.f);

	const char* pathToTexture = "F:\\gamedev\\snake_cmake_sfml_stateANDeventManagment\\snake_cmake_sfml_stateANDeventManagment\\src\\introBackgrndSnake.png";
	backTexture.loadFromFile(pathToTexture);
	backSprite.setTexture(backTexture);

	const char* pathToFont = "F:\\gamedev\\snake_cmake_sfml_stateANDeventManagment\\snake_cmake_sfml_stateANDeventManagment\\src\\arial.ttf";
	font.loadFromFile(pathToFont);

	menuTitle.setFont(font);
	menuTitle.setString("Main Menu");
	menuTitle.setCharacterSize(36);

	sf::FloatRect textDimensions = menuTitle.getLocalBounds();
	menuTitle.setOrigin(textDimensions.left + textDimensions.width / 2,
		textDimensions.top + textDimensions.height / 2);
	menuTitle.setPosition(400, 100);

	for (int i = 0; i < 3; i++)
	{
		sf::Vector2f currentICenterPosition(startingButtonPosition.x,
			(startingButtonPosition.y + i * (buttonSize.y + BUTTON_PADDING)));

		buttonLabels[i].setFont(font);
		buttonLabels[i].setCharacterSize(18);
		buttonLabels[i].setString(strLabels[i]);
		buttonLabels[i].setColor(sf::Color::White);
		sf::FloatRect labelDimensions = buttonLabels[i].getLocalBounds();
		buttonLabels[i].setOrigin(labelDimensions.left + labelDimensions.width / 2,
			labelDimensions.top + labelDimensions.height / 2);
		buttonLabels[i].setPosition(currentICenterPosition);

		buttons[i].setSize(buttonSize);
		buttons[i].setFillColor(sf::Color::Red);
		buttons[i].setOrigin(buttonSize.x / 2, buttonSize.y / 2);
		buttons[i].setPosition(currentICenterPosition);

	}

	EventManager* manager = stateManager->GetContext()->window->GetEventManager();
	manager->AddCallback(StateType::MainMenu,
		"Mouse_Left", &MainMenuState::MouseClick, this);

}

void MainMenuState::OnDestroy()
{
	EventManager* manager = stateManager->GetContext()->window->GetEventManager();
	manager->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}

void MainMenuState::Activate()
{
	if (stateManager->HasState(StateType::MainMenu) &&
		buttonLabels[0].getString() == "Play")
	{
		buttonLabels[0].setString("Resume");
		sf::FloatRect labelDimensions = buttonLabels[0].getLocalBounds();
		buttonLabels[0].setOrigin(labelDimensions.left + labelDimensions.width / 2,
			labelDimensions.top + labelDimensions.height / 2);
	}
}

void MainMenuState::Deactivate()
{}

void MainMenuState::Update(const sf::Time& time)
{}

void MainMenuState::Draw()
{
	sf::RenderWindow* wind = stateManager->GetContext()->window->GetRenderWindow();
	wind->draw(backSprite);
	wind->draw(menuTitle);

	for (int i = 0; i < 3; i++)
	{
		wind->draw(buttons[i]);
		wind->draw(buttonLabels[i]);
	}

}


