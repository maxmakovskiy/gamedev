#include "Textbox.h"

Textbox::Textbox()
{
	Setup(3, 14, 150, sf::Vector2f(16, 16));
}

Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	Setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox()
{
	Clear();
}

void Textbox::Setup(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	numOfVisiblesLines = visible;

	// some padding from upper-left corner
	sf::Vector2f offset(8.f, 8.f);

	font.loadFromFile("F:\\gamedev\\snake_game\\snake_game\\src\\arial.ttf");

	content.setFont(font);
	content.setString("");
	content.setCharacterSize(charSize);
	content.setFillColor(sf::Color::White);
	content.setPosition(screenPos + offset);

	backdrop.setSize(sf::Vector2f(width, (visible * charSize * 1.2f)));
	backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	backdrop.setPosition(screenPos);
	
}

void Textbox::Add(std::string message)
{
	messages.push_back(message);
	if (messages.size() < 3) return;
	messages.erase(messages.begin());
}

void Textbox::Clear()
{
	messages.clear();
}

void Textbox::Render(sf::RenderWindow& window)
{
	std::string whole_messages;

	for (int i = 0; i < messages.size(); i++)
	{
		whole_messages.append(messages[i]);
		whole_messages.append("\n");
	}
	
	if (!whole_messages.empty())
	{
		content.setString(whole_messages);
		window.draw(backdrop);
		window.draw(content);
	}

}


