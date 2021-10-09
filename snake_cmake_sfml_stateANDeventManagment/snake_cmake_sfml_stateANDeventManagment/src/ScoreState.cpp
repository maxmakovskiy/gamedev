#include "ScoreState.h"
#include "StateManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

void ScoreState::GoBack(EventDetails* details)
{}

void ScoreState::OnCreate()
{
	LoadScoreTable();

	textboxSize = sf::Vector2f(480.f, 64.f);
	startingTextboxesPosition = sf::Vector2f(400.f, 190.f);

	const char* pathToBackground = "F:\\gamedev\\snake_cmake_sfml_stateANDeventManagment\\snake_cmake_sfml_stateANDeventManagment\\src\\introBackgrndSnake.png";
	backgroundTexture.loadFromFile(pathToBackground);
	backgroundSprite.setTexture(backgroundTexture);

	const char* pathToFont = "F:\\gamedev\\snake_cmake_sfml_stateANDeventManagment\\snake_cmake_sfml_stateANDeventManagment\\src\\arial.ttf";
	font.loadFromFile(pathToFont);

	titleText.setString("Top-5 Score");
	titleText.setFont(font);
	titleText.setCharacterSize(36);
	titleText.setStyle(sf::Text::Bold);

	sf::FloatRect titleDimensions = titleText.getLocalBounds();
	titleText.setOrigin(titleDimensions.left + titleDimensions.width / 2,
		titleDimensions.top + titleDimensions.height / 2);
	titleText.setPosition(400, 100);

	backgroundFormShape.setSize(sf::Vector2f(500, 360));
	backgroundFormShape.setFillColor(sf::Color(255, 255, 255, 150));
	backgroundFormShape.setOrigin(250, 200);
	backgroundFormShape.setPosition(400, 350);
	
	// TODO:
	// - continue setup
	for (int i = 0; i < 5; i++)
	{
		sf::Vector2f iPosition(startingTextboxesPosition.x,
			(startingTextboxesPosition.y + i * (textboxSize.y + PADDING)));
		
		std::stringstream ss;
		ss << scores[i].first << ": " << scores[i].second;
		textboxesText[i].setString(ss.str());
		textboxesText[i].setCharacterSize(24);
		textboxesText[i].setFont(font);
		textboxesText[i].setColor(sf::Color::White);
		textboxesText[i].setStyle(sf::Text::Bold);
		
		sf::FloatRect textDimensions = textboxesText[i].getLocalBounds();
		textboxesText[i].setOrigin(textDimensions.left + textDimensions.width / 2,
			textDimensions.top + textDimensions.height / 2);
		textboxesText[i].setPosition(iPosition);

		textboxesShape[i].setSize(textboxSize);
		textboxesShape[i].setFillColor(sf::Color(156, 185, 7, 200));
		textboxesShape[i].setOrigin(textboxSize.x / 2, textboxSize.y / 2);
		textboxesShape[i].setPosition(iPosition);

	}



}

void ScoreState::OnDestroy()
{}

void ScoreState::Activate()
{}

void ScoreState::Deactivate()
{}

void ScoreState::Update(sf::Time& time)
{}

void ScoreState::Draw()
{
	sf::RenderWindow* wind = stateManager->GetContext()->window->GetRenderWindow();
	wind->draw(backgroundSprite);
	wind->draw(titleText);
	wind->draw(backgroundFormShape);

	for (int i = 0; i < 5; i++)
	{
		wind->draw(textboxesShape[i]);
		wind->draw(textboxesText[i]);
	}

}

void ScoreState::LoadScoreTable()
{
	std::string delim = ":";
	std::ifstream file;

	const char* fileName = "F:\\gamedev\\snake_cmake_sfml_stateANDeventManagment\\snake_cmake_sfml_stateANDeventManagment\\src\\score_table.data";
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "Unable to load data from score_table.data file by given path " << std::endl;
		return;
	}
	
	std::string line;
	while(std::getline(file, line))
	{
		std::stringstream ss(line);
		
		while (!ss.eof())
		{
			std::string value;
			ss >> value;
			int start = 0;
			int end = value.find(delim);

			std::string nickname = value.substr(start, end-start);
			int score = stoi(value.substr(end+delim.length(), 
				value.find(delim, end+delim.length())));
			
			scores.push_back(std::pair<std::string, int>(nickname, score));
		}

	}

	file.close();
}


