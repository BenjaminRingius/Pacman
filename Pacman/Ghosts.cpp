#include "Ghosts.h"

// Later on we are going to make this draw system better


void Ghosts::draw(sf::RenderWindow& window) {

	sf::Texture sprite;
	sf::Sprite ghost;

	sprite.loadFromFile("Sprites/BlinkyFrame.png", sf::IntRect(0, 0, cell_size, cell_size));

	sprite.Normalized;
	ghost.setTexture(sprite);
	ghost.setPosition(position.x, position.y);
	window.draw(ghost);

}

void Ghosts::set_position(short x, short y) {
	position = { x, y };
}

void Ghosts::update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman) {
	short x = pacman.get_pacman_position().x;
	short y = pacman.get_pacman_position().y;

	std::cout << x << " | " << y << std::endl;
}


// all kinds of targets will be in here and the algorithm itself
void Ghosts::targetPacman(short targetX, short targetY) {

}