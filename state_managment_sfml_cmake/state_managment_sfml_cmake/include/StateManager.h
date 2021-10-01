#include <vector>
#include <unordered_map>
#include <functional>

// forward declaration of some classes
class Window;
class EventManger;
class BaseState;

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
	EventManger* eventManager;

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
using StateFactory = std::unordered_man<StateType, std::function<BaseState*(void)>;










