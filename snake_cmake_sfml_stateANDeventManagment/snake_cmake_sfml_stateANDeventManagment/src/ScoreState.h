#include "BaseState.h"
#include "EventManager.h"
#include <vector>

// SCORE:
// Name1 : 123123
// Name2 : 1233
// Name3 : 55
using ScoreContainer = std::vector<std::pair<std::string, std::int>>;

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
	void WriteChangesToFile(const char* name);
	void WriteToScoreTable();
	void LoadScoreTable();



};

