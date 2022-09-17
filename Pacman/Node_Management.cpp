#include "Node_Management.h"

std::vector<std::vector<short>> point_out_nodes(std::array<std::array<Cells, map_width>, map_height>& map) {

	std::vector<std::vector<short>> nodes;

	std::vector<short> node = { NULL, NULL };

	for (char row = 0; row < map_height; row++) {

		for (char col = 0; col < map_width; col++) {

			if (map[row][col] == Cells::Empty || map[row][col] == Cells::Food || map[row][col] == Cells::Berries) {

				if (map[row - 1][col] != Cells::Wall && map[row][col - 1] != Cells::Wall || map[row][col - 1] != Cells::Wall && map[row + 1][col] != Cells::Wall ||
					map[row - 1][col] != Cells::Wall && map[row][col + 1] != Cells::Wall || map[row + 1][col] != Cells::Wall && map[row][col + 1] != Cells::Wall) {

					node = { static_cast<short>(row * cell_size), static_cast<short>(col * cell_size) };
					nodes.push_back(node);
				}
			}
		}
	}
	return nodes;
}