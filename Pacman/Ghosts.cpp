#include "Ghosts.h"

// Later on we are going to make this draw system better


Ghosts::Ghosts(char ghost_id) :
	id(ghost_id)
{

}


void Ghosts::draw(sf::RenderWindow& window) {


	unsigned char frame = static_cast<unsigned char>(floor(anime_timer / static_cast<float>(ghost_anime_speed)));

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

void Ghosts::set_position(short x, short y) {
	position = { x, y };
}

float Ghosts::get_distance(char direction) {

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


void Ghosts::update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, Ghosts& blinky, std::vector<std::vector<short>>& nodes) {

	direction = calulated_target(target.x, target.y, map, nodes);

	switch (id) {
	case 0:
		target = pacman.get_position();
		break;
	case 1:

		switch (pacman.get_direction()) {
			case 0:
			{
				target.x = pacman.get_position().x - (4 * cell_size);
				target.y = pacman.get_position().y - (4 * cell_size);
				break;
			}
			case 1:
			{
				target.x = pacman.get_position().x - (4 * cell_size);
				target.y = pacman.get_position().y;
				break;
			}
			case 2:
			{
				target.x = pacman.get_position().x;
				target.y = pacman.get_position().y + (4 * cell_size);
				break;
			}
			case 3:
			{
				target.x = pacman.get_position().x + (4 * cell_size);
				target.y = pacman.get_position().y;
			}
		}
		break;
	case 2:

		switch (pacman.get_direction()) {
			case 0:
			{
				target.x = pacman.get_position().x - (2 * cell_size);
				target.y = pacman.get_position().y - (2 * cell_size);
				break;
			}
			case 1:
			{
				target.x = pacman.get_position().x - (2 * cell_size);
				target.y = pacman.get_position().y;
				break;
			}
			case 2:
			{
				target.x = pacman.get_position().x;
				target.y = pacman.get_position().y + (2 * cell_size);
				break;
			}
			case 3:
			{
				target.x = pacman.get_position().x + (2 * cell_size);
				target.y = pacman.get_position().y;
			}
		}

		target.x += target.x - blinky.get_position().x;
		target.y += target.y - blinky.get_position().y;

		break;
	case 3:
		target = pacman.get_position();
	}
		

	// Ghost movement

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

char Ghosts::calulated_target(short targetX, short targetY, std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes) {

	static char way_to_target = 1; // final direction so 0 is up, 1 is left, 2 is down and 3 is right

	std::array<Cells, 4> cells{};
	cells[0] = map[floor(position.y / cell_size) - 1][position.x / cell_size];
	cells[1] = map[position.y / cell_size][floor(position.x / cell_size) - 1];
	cells[2] = map[ceil((position.y + cell_size - 1) / cell_size) + 1][position.x / cell_size];
	cells[3] = map[position.y / cell_size][ceil((position.x + cell_size - 1) / cell_size) + 1];

	std::vector<short> node_position = { position.y, position.x };

	// the path finding

	char optimal_direction = 4;
	char available_ways = 0;

	for (char init = 0; init < nodes.size(); init++) {
		if (nodes[init] == node_position) {


			for (char a = 0; a < 4; a++) {

				if (a == (2 + way_to_target) % 4) {
					continue;
				}
				else if (Cells::Wall != cells[a] && Cells::Door != cells[a]) {

					if (4 == optimal_direction) {
						optimal_direction = a;
					}
					available_ways++;

					if (get_distance(a) < get_distance(optimal_direction)) {
						optimal_direction = a;
					}
				}

			}

			if (1 < available_ways) {
				way_to_target = optimal_direction;
			}
			else {

				if (4 == optimal_direction) {
					way_to_target = (2 + way_to_target) % 4;
				}
				else {
					way_to_target = optimal_direction;
				}
			}

		}
	}

	return way_to_target;
}

Position Ghosts::get_position() {
	return position;
}