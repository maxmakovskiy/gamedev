#include <iostream>

#include "game.hpp"

int main()
{
    lines::Game game;
    while(!game.GetWindow().IsDone())
    {
       game.Update();
       game.Render();
    }

    return 0;
}
