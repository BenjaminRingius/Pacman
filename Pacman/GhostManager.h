#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Pacman.h"
#include "Ghost.h"


class GhostManager {
private:
	char current_mode;

	short mode_timer;

	std::array<Ghost, 4> ghosts = { Ghost(0), Ghost(1), Ghost(2), Ghost(3) };

public:
	void draw(sf::RenderWindow& window);
	void reset(const std::array<Position, 4>& ghost_positions);
	void update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, std::vector<std::vector<short>>& nodes);
};
