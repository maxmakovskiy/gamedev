#ifndef LINES_WINDOW_H_
#define LINES_WINDOW_H_

#include <SFML/Graphics.hpp>

namespace lines {

class Window
{
public:
    Window();
    Window(const std::string& title, const sf::Vector2u& windowSize);
    ~Window();

    void HandleEvents();

    void BeginDraw();
    void Draw(const sf::Drawable& drawable);
    void EndDraw();

    void ToggleFullscreen();

    bool IsFullscreen() const;
    bool IsDone() const;
    sf::Vector2u GetWindowSize() const;

private:
    sf::RenderWindow renderWindow_;
    std::string title_;
    sf::Vector2u size_;
    bool fullscreen_;
    bool done_;

    void Create();
    void Setup(const std::string& title, const sf::Vector2u& windowSize);
    void Destroy();

};

}

#endif
