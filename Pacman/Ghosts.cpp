#include "Ghosts.h"

// Later on we are going to make this draw system better


void Ghosts::draw(sf::RenderWindow& window) {

	sf::Texture sprite;
	sf::Sprite ghost;

	sprite.loadFromFile("Sprites/BlinkyFrame.png", sf::IntRect(0, 0, cell_size, cell_size));
	
	ghost.setTexture(sprite);
	ghost.setPosition(position.x, position.y);
	window.draw(ghost);

}

void Ghosts::set_position(short x, short y) {
	position = { x, y };
}

void Ghosts::update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, std::vector<std::vector<short>>& nodes) {
	short x = pacman.get_position().x;
	short y = pacman.get_position().y;

	//std::cout << "x: " << x << " | " << "y: " << y << std::endl;

	direction = Ghosts::target(x, y, map, nodes);

	// Ghost movement

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
		if (1 == map_collision(position.x, position.y, map, 0)) {
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
		}
	}

	if (-cell_size >= position.x && direction == 1) {
		position.x = cell_size * map_width;
	}
	else if (cell_size * map_width <= position.x && direction == 3) {
		position.x = -cell_size;
	}

}


/*	all kinds of targets will be in hereand the algorithm itself,
	the collision neighbour algorithm will be checked in a separete function but the nodes exists in "Node_Management.h"*/
char Ghosts::target(short targetX, short targetY, std::array<std::array<Cells, map_width>, map_height>& map, std::vector<std::vector<short>>& nodes) {

	static short way_to_target = 1; // final direction so 0 is up, 1 is left, 2 is down and 3 is right

	std::array<Cells, 4> cells{};
	cells[0] = map[floor(position.y / cell_size) - 1][position.x / cell_size];
	cells[1] = map[position.y / cell_size][floor(position.x / cell_size) - 1];
	cells[2] = map[ceil((position.y + cell_size - 1) / cell_size) + 1][position.x / cell_size];
	cells[3] = map[position.y / cell_size][ceil((position.x + cell_size - 1) / cell_size) + 1];

	std::vector<short> node_position = { position.y, position.x };


	// the chase algorithm, but for now we use random just to see how the ghost will act, it isn't a good random walking, just wanted to see if the ghost would go through walls
	// but it didn't so that's good, of course we will need that random walking when thay get into frightened mode

	for (char init = 0; init < nodes.size(); init++)
		if (nodes[init] == node_position) {
			if (cells[way_to_target] == Cells::Wall && cells[(way_to_target + 3) % 4] == Cells::Wall && cells[(way_to_target + 1) % 4] != Cells::Wall) {
				way_to_target = (way_to_target + 2) % 4;
			}
			else {
				way_to_target = rand() % 4;
			}
		}

	std::cout << way_to_target << std::endl;

	return static_cast<char>(way_to_target);
}