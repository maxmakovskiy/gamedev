#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using MessageContainer = std::vector<std::string>;

class Textbox
{
public:
	Textbox();
	Textbox(int visible, int charSize, int width, sf::Vector2f screenPos);
	~Textbox();

	void Setup(int visible, int charSize, int width, sf::Vector2f screenPos);
	void Add(std::string message);
	void Clear();

	void Render(sf::RenderWindow& window);

private:
	MessageContainer messages;
	int numOfVisiblesLines;
	
	sf::RectangleShape backdrop;
	sf::Font font;
	sf::Text content;
};
