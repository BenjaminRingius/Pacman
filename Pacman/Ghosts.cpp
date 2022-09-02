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

void Ghosts::update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman) {
	short x = pacman.get_position().x;
	short y = pacman.get_position().y;

	std::cout << "x: " << x << " | " << "y: " << y << std::endl;

	direction = Ghosts::target(x, y);

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
char Ghosts::target(short targetX, short targetY) {

	static char way_to_target = 1; // final direction so 0 is up, 1 is left, 2 is down and 3 is right

	return way_to_target;
}