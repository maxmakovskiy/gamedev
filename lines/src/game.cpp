#include "game.hpp"

namespace lines {

Game::Game()
    : window_("Lines", sf::Vector2u(800, 600))
{
    texture_.loadFromFile("//home//xemerius//devs//gamedev//simple_drawing_sfml//simple_drawing_sfml//src//ballOrange.png");
    sprite_.setTexture(texture_);
}

void Game::Update()
{
    window_.HandleEvents();
}

const Window& Game::GetWindow()
{
    return window_;
}

void Game::Render()
{
    window_.BeginDraw();
    window_.Draw(sprite_);
    window_.EndDraw();
}

}
