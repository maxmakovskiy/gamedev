#include "window.hpp"

namespace lines {

Window::Window()
{
    Setup("Lines", sf::Vector2u(720, 480));
    Create();
}

Window::Window(const std::string& title, const sf::Vector2u& windowSize)
{
    Setup(title, windowSize);
    Create();
}

Window::~Window()
{
    Destroy();
}

void Window::BeginDraw()
{
    renderWindow_.clear(sf::Color::White);
}

void Window::Draw(const sf::Drawable& drawable)
{
    renderWindow_.draw(drawable);
}

void Window::EndDraw()
{
    renderWindow_.display();
}

void Window::Create()
{
    sf::Uint32 style = fullscreen_ ? sf::Style::Fullscreen : sf::Style::Default;
    renderWindow_.create(sf::VideoMode(size_.x, size_.y, 32), title_, style);
}

void Window::Setup(const std::string& title, const sf::Vector2u& windowSize)
{
    fullscreen_ = false;
    done_ = false;
    title_ = title;
    size_ = windowSize;
}

void Window::ToggleFullscreen()
{
    fullscreen_ = !fullscreen_;
    Destroy();
    Create();
}

bool Window::IsFullscreen() const
{
    return fullscreen_;
}

bool Window::IsDone() const
{
    return done_;
}

sf::Vector2u Window::GetWindowSize() const
{
    return size_;
}

void Window::Destroy()
{
    renderWindow_.close();
}

void Window::HandleEvents()
{
    sf::Event event;
    while (renderWindow_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            renderWindow_.close();
        } else if (event.type == sf::Event::KeyPressed &&
                   event.key.code == sf::Keyboard::F5)
        {
            ToggleFullscreen();
        }
    }
}

}




