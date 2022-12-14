#include "GhostManager.h"

void GhostManager::reset(const std::array<Position, 4>& ghost_positions) {

	for (char n = 0; n < 4; n++) {
		ghosts[n].set_position(ghost_positions[n].x, ghost_positions[n].y);
	}

	for (Ghost& ghost : ghosts) {
		ghost.reset(ghosts[0].get_position(), 1);
	}
}

void GhostManager::draw(sf::RenderWindow& window) {

	for (Ghost& ghost : ghosts) {

		ghost.draw(window);
	}
}

bool GhostManager::update(std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, std::vector<std::vector<short>>& nodes) {

	for (Ghost& ghost : ghosts) {
		ghost.update(map, pacman, ghosts[0], nodes);

		if (1 == ghost.pacman_collision(pacman.get_position())) {
			return 1;
		}
	}
	return 0;
}