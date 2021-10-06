#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "EventManager.h"
#include "IntroState.h"
#include "MainMenuState.h"
#include "GameState.h"
//#include "PausedState.h"
#include "Window.h"

// forward declaration of some classes
//class Window;

// enumeration of all existing state types in this game
enum class StateType : int
{
	Intro = 1,
	MainMenu,
	Game,
	Paused,
	GameOver,
	Credits
};

// data type for having pointers to most used classes
struct SharedContext
{
	Window* window;
	EventManager* eventManager;

	SharedContext()
		: window(nullptr)
		, eventManager(nullptr)
	{}
};

// aliases for most convinient using
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
// container for custom functions
// this functions automatically produces objects of different types
// derived from the BaseState class
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
public:
	StateManager(SharedContext* sharedContext);
	~StateManager();

	void Update(sf::Time& delataTime);
	void Draw();

	void ProcessRequests();

	inline SharedContext* GetContext() { return sharedContext; }
	//if we currently have certain state on the stack
	bool HasState(const StateType& stateType);

	// using for switch from current state to given state
	void SwitchTo(const StateType& stateType);
	// removing state from the stack by its type
	void Remove(const StateType& stateType);

private:
	SharedContext* sharedContext;
	StateContainer states;
	StateFactory stateFactory;

	// we cannot simply delete state from container at any time,
	// toRemove serves to keep tracking states which
	// we want to delete and deleting them in the end of game loop
	TypeContainer toRemove;

	void CreateState(const StateType& stateType);
	void RemoveState(const StateType& stateType);

	template<class T>
	void RegisterState(const StateType& stateType)
	{
		stateFactory[stateType] = [this]() -> BaseState*
		{ return new T(this); };
	}

};








