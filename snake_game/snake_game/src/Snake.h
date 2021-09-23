#pragma once

#include <SFML/Graphics.hpp>

// shortcut jush like define but more safe
using SnakeContainer = std::vector<SnakeSegment>;

struct SnakeSegment
{
	// position of the segment on the grid
	sf::Vector2i position;

	SnakeSegment(int x, int y) : position(x, y) {}
};

enum class Direction
{
	None = 0,
	Up,
	Down,
	Left,
	Right
};


