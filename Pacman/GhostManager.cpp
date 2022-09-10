#include "GhostManager.h"

void GhostManager::reset(std::array<Position, 4>& ghost_positions) {

	for (char ghost = 0; ghost < 4; ghost++) {
		ghosts[ghost].set_position(ghost_positions[ghost].x, ghost_positions[ghost].y);
	}
}

void GhostManager::update(sf::RenderWindow& window, std::array<std::array<Cells, map_width>, map_height>& map, Pacman& pacman, std::vector<std::vector<short>>& nodes) {


	for (Ghosts& ghost : ghosts) {
		ghost.draw(window);
		ghost.update(map, pacman, ghosts[0], nodes);
	}
}