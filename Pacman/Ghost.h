#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Globals.h"
#include "Collision.h"
#include "Pacman.h"
#include "Node_Management.h"

class Ghost
{
private:
	Position position;
	Position target;

	char direction;
	char id;
	unsigned char anime_timer = 0;

public:
	Ghost(char ghost_id);

	void draw(sf::RenderWindow& window);
	void set_position(short x, short y);
	float get_distance(char direction);
	void update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, Ghost& blinky, std::vector<std::vector<short>>& nodes);
	char caclulated_target(short targetX, short targetY, std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes);

	Position get_position();
};