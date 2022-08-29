#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Globals.h"
#include "Collision.h"

class Ghosts
{
	Position position;

public:
	void draw(sf::RenderWindow& window);
	void set_position(short x, short y);
	void update(std::array<std::array<Cells, map_width>, map_height>& map, sf::Event& events);
	void targetPacman(short targetX, short targetY);
};