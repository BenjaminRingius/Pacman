#include "Pacman.h"


void Pacman::draw(sf::RenderWindow& window) {

	sf::Texture sprite;
	sf::Sprite pacman;

	char frame = floor(anime_timer / pac_anime_speed);

	sprite.loadFromFile("Sprites/PacmanFrames.png", sf::IntRect(cell_size * frame, cell_size * direction, cell_size, cell_size));

	if (1 == anime_switch) {
		anime_timer = (1 + anime_timer) % (pac_anime_frames * pac_anime_speed);
	}
	sprite.Normalized;
	pacman.setTexture(sprite);
	pacman.setPosition(position.x, position.y);
	window.draw(pacman);
}

void Pacman::set_position(short x, short y) {

	position = { x, y };
}

void Pacman::update(std::array<std::array<Cells, map_width>, map_height>& map) {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		newDir = 0;
		if (direction == 2)
			direction = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		newDir = 1;
		if (direction == 3)
			direction = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		newDir = 2;
		if (direction == 0)
			direction = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		newDir = 3;
		if (direction == 1)
			direction = 3;
	}

	switch (direction) {

	case 0:
		position.y -= pac_speed;
		break;
	case 1:
		position.x -= pac_speed;
		break;
	case 2:
		position.y += pac_speed;
		break;
	case 3:
		position.x += pac_speed;
	}

	if (0 == (0 >= position.x || cell_size * map_width <= position.x + cell_size - 1)) {
		if (1 == map_collision(position.x, position.y, map)) {
			switch (direction) {

			case 0:
				position.y += pac_speed;
				break;
			case 1:
				position.x += pac_speed;
				break;
			case 2:
				position.y -= pac_speed;
				break;
			case 3:
				position.x -= pac_speed;
			}
			anime_switch = 0;
		}
		else {
			anime_switch = 1;
		}
	}
	else {
		anime_switch = 1;
	}

	if (-cell_size >= position.x && direction == 1) {
		position.x = cell_size * map_width;
	}
	else if (cell_size * map_width <= position.x && direction == 3) {
		position.x = -cell_size;
	}
}


void Pacman::direction_management(std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes) {

	short pacDown = position.y + cell_size - 1;
	short pacRight = position.x + cell_size - 1;

	std::array<Cells, 4> cells{};
	cells[0] = map[floor(position.y / cell_size) - 1][position.x / cell_size];
	cells[1] = map[position.y / cell_size][floor(position.x / cell_size) - 1];
	cells[2] = map[ceil(pacDown / cell_size) + 1][position.x / cell_size];
	cells[3] = map[position.y / cell_size][ceil(pacRight / cell_size) + 1];

	std::vector<short> positions = { position.y, position.x };

	for (short init = 0; init < nodes.size(); init++) {
		if (nodes[init] == positions) {
			if (newDir == 0 && cells[0] != Cells::Wall) {
				direction = 0;
			}
			else if (newDir == 1 && cells[1] != Cells::Wall) {
				direction = 1;
			}
			else if (newDir == 2 && cells[2] != Cells::Wall && cells[2] != Cells::Door) {
				direction = 2;
			}
			else if (newDir == 3 && cells[3] != Cells::Wall) {
				direction = 3;
			}
		}
	}
}

Position Pacman::get_position() {
	return position;
}