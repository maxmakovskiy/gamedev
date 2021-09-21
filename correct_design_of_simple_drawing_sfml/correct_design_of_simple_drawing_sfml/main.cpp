#include "game.h" 


int main() 
{
	Game game;

	while (!game.GetWindow()->IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
	}


	return 0;
}