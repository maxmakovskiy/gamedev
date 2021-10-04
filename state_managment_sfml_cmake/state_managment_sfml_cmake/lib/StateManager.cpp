#include <../include/StateManager.h>

StateManager::StateManager(SharedContext* sharedContext)
	: sharedContext(sharedContext)
{
	RegisterState<IntroState>(StateType::Intro);
	RegisterState<MainMenuState>(StateType::MainMenu);
	RegisterState<GameState>(StateType::Game);
//	RegisterState<PauseState>(StateType::Paused); 
}

StateManager::~StateManager()
{
	for (auto& state : states)
	{
		state.second->OnDestroy();
		delete state.second;
	}

}

void StateManager::Draw()
{
	// if we got nothing to draw
	if (states.empty()) return;

	if (states.back().second->IsTransparent() &&
		states.size() > 1)
	{ // if we have more than 1 element in container and it is transparent
		std::vector<std::pair<StateType, BaseState*>>::iterator itr = states.end();

		// iterate over vector from back to front
		// and search first transperent state
		// if we found it then break the loop
		while(itr != states.begin())
		{
			if (itr != states.end() &&
				(!itr->second->IsTransparent()))
			{
				break;
			}

			itr--;
		}

		// using current itr position
		// start by it and forward iterate to the end of vector
		// and call Draw() method for each state
		for (; itr != states.end(); itr++)
		{
			itr->second->Draw();
		}
	}
	else // else we have just one state in container
	{ // just draw it
		states.back().second->Draw();
	}
}

void StateManager::Update(const sf::Time& deltaTime)
{
	if (states.empty()) return;

	if (states.back().second->IsTranscendent() &&
		states.size() > 1)
	{
		std::vector<std::pair<StateType, BaseState*>>::iterator itr = states.end();

		while(itr != states.begin())
		{
			if (itr != states.end() &&
				(!itr->second->IsTranscendent()))
			{
				break;
			}

			itr--;
		}

		// using current itr position
		// start by it and forward iterate to the end of vector
		// and call Draw() method for each state
		for (; itr != states.end(); itr++)
		{
			itr->second->Update(deltaTime);
		}
	}
	else
	{
		states.back().second->Update(deltaTime);
	}

}

bool StateManager::HasState(const StateType& stateType)
{
	for (auto itr = states.begin();
		itr != states.end(); itr++)
	{
		if (itr->first == stateType)
		{
			auto removeItr = std::find(
				toRemove.begin(), toRemove.end(), stateType);

			// if searched state contains in stateContainer
			// and does not contain in container toRemove
			// then return true
			if (removeItr == toRemove.end())
				return true;

			return false;
		}
	}

	return false;
}

void StateManager::Remove(const StateType& stateType)
{
	toRemove.push_back(stateType);
}

void StateManager::ProcessRequests()
{
	while(toRemove.begin() != toRemove.end())
	{
		RemoveState(*toRemove.begin()); // take care of resource de-allocation
		toRemove.erase(toRemove.begin()); // and then remove element
	}
}

void StateManager::SwitchTo(const StateType& stateType)
{
	// since eventManager keeps track what are state now game has
	// we need to force new state
	sharedContext->eventManager->SetCurrentState(stateType);

	for (std::vector<std::pair<StateType, BaseState*>>::iterator itr = states.begin();
		 itr != states.end(); itr++)
	{
		// if given stateType already contains
		// in the states container 
		if (itr->first == stateType)
		{
			// deactivate state that is the top of the stack
			states.back().second->Deactivate();

			// get data from matched state
			StateType tmpStateType = itr->first;
			BaseState* tmpState = itr->second;

			// remove founded state from the its current position
			// and push it on the top of stack
			states.erase(itr);
			states.emplace_back(tmpStateType, tmpState);
			tmpState->Activate();
			return;
		}
	}

	// if states container doesn't not empty
	// but matches not found
	if (!states.empty()) 
	{
		// then deactivate current top state
		states.back().second->Deactivate();
	}
	// create state by given type
	// and activate him
	CreateState(stateType);
	states.back().second->Activate();
}

void StateManager::CreateState(const StateType& stateType)
{
	// newState - iterator which pointed to the element with stateType key
	auto newState = stateFactory.find(stateType);
	// if element by stateType key is not founded
	if (newState == stateFactory.end()) return;

	// invoke second() as function 
	// which returns a pointer to newly created state class
	BaseState* state = newState->second();
	// push newly created state and call OnCreate for do its iternal logic
	states.emplace_back(stateType, state);
	state->OnCreate();
}

void StateManager::RemoveState(const StateType& stateType)
{
	for (std::vector<std::pair<StateType, BaseState*>>::iterator itr = states.begin();
		 itr != states.end(); itr++)
	{
		if (itr->first == stateType)
		{
			itr->second->OnDestroy();
			delete itr->second;
			states.erase(itr);
			return;
		}
	}
}



