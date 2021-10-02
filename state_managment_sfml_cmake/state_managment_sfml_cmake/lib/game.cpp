#include "../include/game.h"

Game::Game()
	: window("Bouncing Ball", sf::Vector2u(800, 600))
	, stateManager(&sharedContext)
{
	// setup context
	sharedContext.window = &window;
	sharedContext.eventManager = window.GetEventManager();
	stateManager.SwitchTo(StateType:Intro);

/*	const char* pathToFile = "F:\\gamedev\\correct_design_of_simple_drawing_sfml\\correct_design_of_simple_drawing_sfml\\ballYellow.png";
	if (!this->texture.loadFromFile(pathToFile))
	{
		fprintf(stderr, "Error occurs while load texture from file by path: %s", pathToFile);
	}
	
	sprite.setTexture(this->texture);
	speed = sf::Vector2f(200.0f, 200.0f);

	int size = texture.getSize().x;
	sprite.setOrigin(size / 2, size / 2);

	// Setup callback
	window.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);
*/
}

Game::~Game() {}

void Game::HandleInput() {}

void Game::Update()
{
	window.Update(); // update window events
	stateManager.Update(elapsed);
}

void Game::Render()
{
	window.BeginDraw(); // clear
	stateManager.Draw();	
	//window.Draw(this->sprite);
	window.EndDraw(); // display
}

Window* Game::GetWindow()
{
	return &window;
}

void Game::MoveSprite(EventDetails* details)
{
	// get current mouse position relative to current window
	sf::Vector2i mousePosition = window.GetEventManager()->GetMousePosition(window.GetRenderWindow());

	sprite.setPosition(mousePosition.x, mousePosition.y);
	std::cout << "Moving ball to (" << mousePosition.x << ":" << mousePosition.y << ");" << std::endl;
}

sf::Time Game::GetElaped()
{
	return elapsed;
}

void Game::RestartClock()
{
	elapsed = clock.restart();
}

void Game::LateUpdate()
{
	stateManager.ProcessRequests();
	RestartClock();
}