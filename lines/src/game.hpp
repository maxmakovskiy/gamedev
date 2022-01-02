#ifndef LINES_GAME_H_
#define LINES_GAME_H_

#include "window.hpp"

namespace lines {

class Game
{
public:
    Game();

    void Update();
    void Render();

    const Window& GetWindow();
private:
    Window window_;
    sf::Texture texture_;
    sf::Sprite sprite_;


};

}

#endif
