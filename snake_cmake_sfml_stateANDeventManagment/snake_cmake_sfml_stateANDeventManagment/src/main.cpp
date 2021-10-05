#include "game.h" 

int main() 
{
	Game game;

	while (!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Render();
		game.LateUpdate();
	}

	return 0;
}