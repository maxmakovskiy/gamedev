#include <SFML/Graphics.hpp>
#include <stdio.h>


void CalculateNewDirection(const sf::RenderWindow&, const sf::Sprite&, const sf::Vector2u&, sf::Vector2f&);

int main()
{
	sf::RenderWindow window(sf::VideoMode(720, 480), "Bouncing ball");

	sf::Texture textureCyanBall;
	sf::Texture textureOrangeBall;
	sf::Texture textureYellowBall;

	sf::Sprite spriteCyanBall;
	sf::Sprite spriteOrangeBall;
	sf::Sprite spriteYellowBall;

	sf::Vector2u sizeOfOneBall;

	// representing speed by step of move that ball does at one loop iteration
	sf::Vector2f speedOfCyanBall(0.08f, 0.08f);
	sf::Vector2f speedOfOrangeBall(0.08f, 0.08f);
	sf::Vector2f speedOfYellowBall(0.08f, 0.08f);

	const char* pathToCyanBallImage = "F:\\gamedev\\simple_drawing_sfml\\simple_drawing_sfml\\src\\ballCyan.png";
	if (!textureCyanBall.loadFromFile(pathToCyanBallImage))
	{
		fprintf(stderr, "Error with load the image from path: %s", pathToCyanBallImage);
	}

	const char* pathToOrangeBallImage = "F:\\gamedev\\simple_drawing_sfml\\simple_drawing_sfml\\src\\ballOrange.png";
	if (!textureOrangeBall.loadFromFile(pathToOrangeBallImage))
	{
		fprintf(stderr, "Error with load the image from path: %s", pathToOrangeBallImage);
	}

	const char* pathToYellowBallImage = "F:\\gamedev\\simple_drawing_sfml\\simple_drawing_sfml\\src\\ballYellow.png";
	if (!textureYellowBall.loadFromFile(pathToYellowBallImage))
	{
		fprintf(stderr, "Error with load the image from path: %s", pathToYellowBallImage);
	}

	spriteCyanBall.setTexture(textureCyanBall);
	spriteOrangeBall.setTexture(textureOrangeBall);
	spriteYellowBall.setTexture(textureYellowBall);

	// get size of cyan ball sprite
	sizeOfOneBall.x = textureCyanBall.getSize().x;
	sizeOfOneBall.y = textureCyanBall.getSize().y;
	
	// set start coordinates of sprites
	spriteCyanBall.setOrigin(sizeOfOneBall.x / 2, sizeOfOneBall.y / 2);
	spriteOrangeBall.setOrigin(sizeOfOneBall.x / 2, sizeOfOneBall.y / 2);
	spriteYellowBall.setOrigin(sizeOfOneBall.x / 2, sizeOfOneBall.y / 2);

	// set Start position of sprites
	//spriteCyanBall.setPosition(sizeOfOneBall.x / 2, sizeOfOneBall.y / 2);
	spriteOrangeBall.setPosition(sizeOfOneBall.x * 2, sizeOfOneBall.y * 1.2f);
	spriteYellowBall.setPosition(sizeOfOneBall.x * 3.5f, sizeOfOneBall.y * 0.5f);

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
	
		CalculateNewDirection(window, spriteCyanBall, sizeOfOneBall, speedOfCyanBall);
		CalculateNewDirection(window, spriteOrangeBall, sizeOfOneBall, speedOfOrangeBall);
		CalculateNewDirection(window, spriteYellowBall, sizeOfOneBall, speedOfYellowBall);

		spriteCyanBall.setPosition(spriteCyanBall.getPosition() + speedOfCyanBall);
		spriteOrangeBall.setPosition(spriteOrangeBall.getPosition() + speedOfOrangeBall);
		spriteYellowBall.setPosition(spriteYellowBall.getPosition() + speedOfYellowBall);

		window.clear(sf::Color::Black);

		window.draw(spriteCyanBall);
		window.draw(spriteOrangeBall);
		window.draw(spriteYellowBall);

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