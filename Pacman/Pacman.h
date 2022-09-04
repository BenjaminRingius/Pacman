#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Globals.h"
#include "Collision.h"

class Pacman
{
	char direction = 1;
	char newDir;
	char anime_timer = 0;
	
	bool anime_switch;

	Position position;

public:
	void draw(sf::RenderWindow& window);
	void set_position(short x, short y);
	void update(std::array<std::array<Cells, map_width>, map_height>& map);
	void direction_management(std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes);

	Position get_position();
	char get_direction();
};