#pragma once
#include <SFML/Graphics.hpp>
// forward declaration StateManager class
// for purpose of exclude recursive definition
// because StateManager will have contains 
// pointer to BaseState class
class StateManager;


class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager* stateManager)
		: stateManager(stateManager)
		, transparent(false)
		, transcendent(false)
	{}

	// couse we use virtual functions
	// and compiler will choose destructor
	// through virtual method table
	virtual ~BaseState() {}

	// get invoked when state is created and pushed on the stack
	virtual void OnCreate() = 0;
	// get invoked when state is removed from the stack
	virtual void OnDestroy() = 0;

	// this two methods is called once
	// when state is moved to the top of the stack
	virtual void Activate() = 0;
	// and when removed from the top position
	virtual void Deactivate() = 0;

	// using for update state and drawing its contents
	virtual void Update(const sf::Time& time) = 0;
	virtual void Draw() = 0;

	inline void SetTransparent(const bool& transparent)
	{
		this->transparent = transparent;
	} 

	inline bool IsTransparent() const { return this->transparent; }

	inline void SetTranscendent(const bool& transcendent) 
	{
		this->transcendent = transcendent;
	}

	inline bool IsTranscendent() const { return this->transcendent; }

	inline StateManager* GetStateManager() { return this->stateManager; } 

protected:
	StateManager* stateManager;

	// these flags indicate
	// if state also needs to render or update
	// a state that came before it
	bool transparent; // for drawing states that come before it
	bool transcendent; // for updating states that come before it
};