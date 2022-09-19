#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Globals.h"
#include "Collision.h"

class Pacman {
private:
	char direction;
	char newDir;
	char anime_direction = 1;
	char anime_timer = 0;
	char frame = 0;

	bool force_anime = 1;
	bool anime_switch = 1;

	Position position;

public:
	void draw(sf::RenderWindow& window);
	void set_position(short x, short y);
	void update(std::array<std::array<Cells, map_width>, map_height>& map);
	void direction_management(std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes);

	Position get_position();
	char get_direction();

	bool start_game();
};