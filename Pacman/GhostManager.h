#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Pacman.h"
#include "Ghosts.h"


class GhostManager
{
	char current_mode;

	short mode_timer;

	std::array<Ghosts, 4> ghosts = { Ghosts(0), Ghosts(1), Ghosts(2), Ghosts(3) };

public:
	void draw(sf::RenderWindow& window);
	void reset(const std::array<Position, 4>& ghost_positions);
	void update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, std::vector<std::vector<short>>& nodes);
};
