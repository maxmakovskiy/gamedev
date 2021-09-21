#include <SFML/Graphics.hpp>
#include <stdio.h>


void CalculateNewDirection(const sf::RenderWindow&, const sf::Sprite&, const sf::Vector2u&, sf::Vector2f&);

int main()
{
	sf::RenderWindow window(sf::VideoMode(720, 480), "Bouncing ball");

	sf::Texture textureCyanBall;
	sf::Sprite spriteCyanBall;

	sf::Vector2u sizeCyanBall;

	// representing speed by step of move that ball does at one loop iteration
	sf::Vector2f speed(0.08f, 0.08f);

	const char* pathToCyanBallImage = "F:\\gamedev\\simple_drawing_sfml\\simple_drawing_sfml\\src\\ballCyan.png";
	if (!textureCyanBall.loadFromFile(pathToCyanBallImage))
	{
		fprintf(stderr, "Error with load the image from path: %s", pathToCyanBallImage);
	}

	spriteCyanBall.setTexture(textureCyanBall);

	// get size of cyan ball sprite
	sizeCyanBall.x = textureCyanBall.getSize().x;
	sizeCyanBall.y = textureCyanBall.getSize().y;
	
	// set start coordinates of spriteCyanBall
	spriteCyanBall.setOrigin(sizeCyanBall.x / 2, sizeCyanBall.y / 2);

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
	
		CalculateNewDirection(window, spriteCyanBall, sizeCyanBall, speed);
		
		spriteCyanBall.setPosition(spriteCyanBall.getPosition() + speed);

		window.clear(sf::Color::Black);
		window.draw(spriteCyanBall);
		window.display();
	}


	return 0;
}

void CalculateNewDirection(const sf::RenderWindow& window, const sf::Sprite& sprite, const sf::Vector2u& size, sf::Vector2f& direction)
{
	if((sprite.getPosition().x + (size.x / 2) > window.getSize().x && direction.x > 0) ||
		(sprite.getPosition().x - (size.x / 2) < 0 && direction.x < 0))
	{
		// Reverse the direction on X axis.
		direction.x = -direction.x;
	}

	if((sprite.getPosition().y + (size.y / 2) > window.getSize().y && direction.y > 0) ||
		(sprite.getPosition().y - (size.y / 2) < 0 && direction.y < 0))
	{
		// Reverse the direction on Y axis.
		direction.y = -direction.y;
	}

}