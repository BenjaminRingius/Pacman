#include "Collision.h"

bool map_collision(short x, short y, std::array<std::array<Cells, map_width>, map_height>& map, bool isPacman) {

	short pacRight = x + cell_size - 1;
	short pacDown = y + cell_size - 1;

	std::array<Cells, 4> cells{};
	cells[0] = map[floor(y / cell_size)][floor(x / cell_size)];
	cells[1] = map[floor(y / cell_size)][ceil(pacRight / cell_size)];
	cells[2] = map[ceil(pacDown / cell_size)][floor(x / cell_size)];
	cells[3] = map[ceil(pacDown / cell_size)][ceil(pacRight / cell_size)];

	for (Cells& cell : cells) {

		if (Cells::Wall == cell) {
			return 1;
		}
	}

	if (1 == isPacman) {

		if (map[(y + cell_size / 2) / cell_size][(x + cell_size / 2) / cell_size] == Cells::Food) {
			map[y / cell_size][x / cell_size] = Cells::Empty;
		}
		else if (map[(y + cell_size / 2) / cell_size][(x + cell_size / 2) / cell_size] == Cells::Berries) {
			map[y / cell_size][x / cell_size] = Cells::Empty;
		}
	}

	return 0;

}