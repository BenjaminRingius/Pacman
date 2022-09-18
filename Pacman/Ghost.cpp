#include "Ghost.h"

// Later on we are going to make this draw system better


Ghost::Ghost(char ghost_id):
	id(ghost_id)
{
}

void Ghost::reset(const Position& exit, bool use_door) {
	ghost_exit = exit;
	target = exit;
	ghost_house = use_door;
}

void Ghost::draw(sf::RenderWindow& window) {

	char frame = static_cast<unsigned char>(floor(anime_timer / static_cast<float>(ghost_anime_speed)));

	sf::Sprite face;
	sf::Sprite body;

	sf::Texture sprite;
	
	sprite.loadFromFile("Sprites/Ghosts.png", sf::IntRect(cell_size * frame, 0, cell_size, cell_size)); 

	body.setTexture(sprite);
	body.setPosition(position.x, position.y);

	switch (id) {
	case 0:
		body.setColor(sf::Color(255, 0, 0));
		break;
	case 1:
		body.setColor(sf::Color(255,182,255));
		break;
	case 2:
		body.setColor(sf::Color(0, 255, 255));
		break;
	case 3:
		body.setColor(sf::Color(255, 182, 85));
	}

	window.draw(body);

	anime_timer = (1 + anime_timer) % (ghost_anime_frames * ghost_anime_speed);
}

void Ghost::set_position(short x, short y) {
	position = { x, y };
}

bool Ghost::pacman_collision(const Position& pacman) {
	if ((position.x / cell_size) == (pacman.x / cell_size) && (position.y / cell_size) == (pacman.y / cell_size)) {
		return 1;
	}
	return 0;
}

void Ghost::update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, Ghost& blinky, std::vector<std::vector<short>>& nodes) {

	if (0 == ghost_house) {
		switch (id) {
		case 0:
			target = pacman.get_position();
			break;
		case 1:
			switch (pacman.get_direction()) {
			case 0:
				target.x = pacman.get_position().x - cell_size * 4;
				target.y = pacman.get_position().y - cell_size * 4;
				break;
			case 1:
				target.x = pacman.get_position().x - cell_size * 4;
				target.y = pacman.get_position().y;
				break;
			case 2:
				target.x = pacman.get_position().x;
				target.y = pacman.get_position().y + cell_size * 4;
				break;
			case 3:
				target.x = pacman.get_position().x + cell_size * 4;
				target.y = pacman.get_position().y;
			}
			break;
		case 2:
			switch (pacman.get_direction()) {
			case 0:
				target.x = pacman.get_position().x - cell_size * 2;
				target.y = pacman.get_position().y - cell_size * 2;
				break;
			case 1:
				target.x = pacman.get_position().x - cell_size * 2;
				target.y = pacman.get_position().y;
				break;
			case 2:
				target.x = pacman.get_position().x;
				target.y = pacman.get_position().y + cell_size * 2;
				break;
			case 3:
				target.x = pacman.get_position().x + cell_size * 2;
				target.y = pacman.get_position().y;
			}
			target.x = (target.x - blinky.get_position().x) * 2;
			target.y = (target.y - blinky.get_position().y) * 2;
			break;

		case 3:
			if (8 * cell_size <= sqrt(pow(position.x - pacman.get_position().x, 2) + pow(position.y - pacman.get_position().y, 2))) {
				target = pacman.get_position();
			}
			else {
				target = { 0, cell_size * (map_height - 1) };
			}

		}
	}
	else {

		//target = ghost_exit;
		if (target.x == position.x && target.y == position.y) {
			ghost_house = 0;
		}
	}
	

	caclulate_target(map, nodes);

	switch (direction) {

	case 0:
		position.y -= ghost_speed;
		break;
	case 1:
		position.x -= ghost_speed;
		break;
	case 2:
		position.y += ghost_speed;
		break;
	case 3:
		position.x += ghost_speed;
	}

	if (0 == (0 >= position.x || cell_size * map_width <= position.x + cell_size - 1)) {
		if (1 == map_collision(position.x, position.y, map, 0)) {
			switch (direction) {

			case 0:
				position.y += ghost_speed;
				break;
			case 1:
				position.x += ghost_speed;
				break;
			case 2:
				position.y -= ghost_speed;
				break;
			case 3:
				position.x -= ghost_speed;
			}
		}
	}

	if (-cell_size >= position.x && direction == 1) {
		position.x = cell_size * map_width;
	}
	else if (cell_size * map_width <= position.x && direction == 3) {
		position.x = -cell_size;
	}
}
float Ghost::get_distance(char direction) {

	short x = position.x;
	short y = position.y;

	switch (direction) {
	case 0:
		y -= ghost_speed;
		break;
	case 1:
		x -= ghost_speed;
		break;
	case 2:
		y += ghost_speed;
		break;
	case 3:
		x += ghost_speed;
	}

	return static_cast<float>(sqrt(pow(x - target.x, 2) + pow(y - target.y, 2)));
}

void Ghost::caclulate_target(std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes) {

	std::array<Cells, 4> cells{};
	cells[0] = map[floor(position.y / cell_size) - 1][position.x / cell_size];
	cells[1] = map[position.y / cell_size][floor(position.x / cell_size) - 1];
	cells[2] = map[ceil((position.y + cell_size - 1) / cell_size) + 1][position.x / cell_size];
	cells[3] = map[position.y / cell_size][ceil((position.x + cell_size - 1) / cell_size) + 1];

	std::vector<short> node_position = { position.y, position.x };

	// the path finding

	char optimal_direction = 4;
	char available_ways = 0;
	
	for (unsigned char init = 0; init < nodes.size(); init++) {
		if (nodes[init] == node_position) {

			for (char a = 0; a < 4; a++) {

				if (a == (2 + direction) % 4) {
					continue;
				}
				if (0 == ghost_house) {
					if (Cells::Wall != cells[a] && Cells::Door != cells[a]) {

						if (4 == optimal_direction) {
							optimal_direction = a;
						}
						available_ways++;

						if (get_distance(a) < get_distance(optimal_direction)) {
							optimal_direction = a;
						}
					}
				}
				else {
					if (Cells::Wall != cells[a]) {

						if (4 == optimal_direction) {
							optimal_direction = a;
						}
						available_ways++;

						if (get_distance(a) < get_distance(optimal_direction)) {
							optimal_direction = a;
						}
					}
				}
			}

			if (1 < available_ways) {
				direction = optimal_direction;
			}
			else {

				if (4 == optimal_direction) {
					direction = (2 + direction) % 4;
				}
				else {
					direction = optimal_direction;
				}
			}

		}
	}
}

Position Ghost::get_position() {
	return position;
}