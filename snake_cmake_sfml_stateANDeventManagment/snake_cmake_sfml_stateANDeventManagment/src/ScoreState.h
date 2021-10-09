#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include <vector>

// SCORE:
// Name1 : 123123
// Name2 : 1233
// Name3 : 55
using ScoreContainer = std::vector<std::pair<std::string, int>>;

class ScoreState : public BaseState
{
public:
	ScoreState(StateManager* stateManager)
		: BaseState(stateManager)
	{}

	void GoBack(EventDetails* details);
	
	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(sf::Time& time);
	void Draw();

private:
	ScoreContainer scores;

	//void WriteChangesToFile(const char* name); // write to the storage 
	//void UpdateScoreTable(); // write to the memory
	void LoadScoreTable(); // load from file

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font font;
	sf::Text titleText;
	sf::RectangleShape backgroundFormShape;
	sf::RectangleShape textboxesShape[5];
	sf::Text textboxesText[5];
	sf::Vector2f textboxSize;
	const int PADDING = 5;
	sf::Vector2f startingTextboxesPosition;

};

