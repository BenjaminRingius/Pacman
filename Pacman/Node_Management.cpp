#include "Node_Management.h"

std::vector<std::vector<short>> point_out_nodes(std::array<std::array<Cells, map_width>, map_height>& map) {

	std::vector<std::vector<short>> nodes = {};

	std::array<Cells, 4> neighbors = {};

	std::vector<short> node = { 0,0 };

	for (short row = 0; row < map_height; row++) {
		for (short col = 0; col < map_width; col++) {

			if (map[row][col] == Cells::Empty || map[row][col] == Cells::Food || map[row][col] == Cells::Berries) {

				neighbors[0] = map[row - 1][col];
				neighbors[1] = map[row][col - 1];
				neighbors[2] = map[row + 1][col];
				neighbors[3] = map[row][col + 1];
				if (neighbors[0] != Cells::Wall && neighbors[1] != Cells::Wall || neighbors[1] != Cells::Wall && neighbors[2] != Cells::Wall ||
					neighbors[0] != Cells::Wall && neighbors[3] != Cells::Wall || neighbors[2] != Cells::Wall && neighbors[3] != Cells::Wall
					) {
					node[0] = row * cell_size;
					node[1] = col * cell_size;
					nodes.push_back(node);
				}
			}
		}
	}
	return nodes;
}