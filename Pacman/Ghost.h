#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Globals.h"
#include "Collision.h"
#include "Pacman.h"
#include "Node_Management.h"

class Ghost {
private:
	char direction;
	char id;
	char anime_timer = 0;
	char frame;
	char ghost_mode = 0; // 0: chase mode, 1: scatter mode, 2: frightened
	char random_direction = direction;

	bool use_door = 1;
	bool anime_switch = 0;
	bool frightened = 0;

	Position ghost_exit;
	Position position;
	Position target;

public:
	Ghost(char ghost_id);

	float get_distance(char direction);
	bool pacman_collision(const Position& pacman);
	
	void reset(const Position& exit, bool door);
	void draw(sf::RenderWindow& window);
	void set_position(short x, short y);
	void update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, Ghost& blinky, std::vector<std::vector<short>>& nodes);
	void switch_mode(char mode);
	void caclulate_target(std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes);
	void go_random(std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes);

	Position get_position();
};