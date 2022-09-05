#include "GhostManager.h"

void GhostManager::reset(const std::array<Position, 4>& ghost_positions) {

	for (char n = 0; n < 4; n++) {
		ghosts[n].set_position(ghost_positions[n].x, ghost_positions[n].y);
	}
}

void GhostManager::draw(sf::RenderWindow& window) {

	for (Ghosts& ghost : ghosts) {

		ghost.draw(window);
	}
}

void GhostManager::update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, std::vector<std::vector<short>>& nodes) {


	for (Ghosts& ghost : ghosts) {
		ghost.update(map, pacman, ghosts[0], nodes);
	}
}