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

	Ghosts::target(x, y);
}


// all kinds of targets will be in here and the algorithm itself
char Ghosts::target(short targetX, short targetY) {

	static char way_to_target = 1; // final direction so 0 is up, 1 is left, 2 is down and 3 is right

	return way_to_target;
}