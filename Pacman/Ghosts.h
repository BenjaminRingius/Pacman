#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Globals.h"
#include "Collision.h"
#include "Pacman.h"
#include "Node_Management.h"

class Ghosts
{
	Position position;

	char direction;

public:
	void draw(sf::RenderWindow& window);
	void set_position(short x, short y);
	void update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, std::vector<std::vector<short>>& nodes);
	char target(short targetX, short targetY, std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes);
};