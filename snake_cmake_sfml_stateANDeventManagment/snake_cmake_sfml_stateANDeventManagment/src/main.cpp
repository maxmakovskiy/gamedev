#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello world");
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(300, 300));
	rect.setFillColor(sf::Color::Red);
	rect.setOrigin(150, 150);
	rect.setPosition(sf::Vector2f(400, 300));
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);
		window.draw(rect);
		window.display();
	}


	return 0;
}