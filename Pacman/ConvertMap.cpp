#include "ConvertMap.h"


std::array<std::array<Cells, map_width>, map_height> convert_map(std::array<std::string, map_height> map, Pacman& pacman, Ghosts& ghost) {

	std::array<std::array<Cells, map_width>, map_height> final_map{};

	for (char i = 0; i < map_height; i++) {

		for (char j = 0; j < map_width; j++) {
			
			switch (map[i][j]) {
			
			case ' ':
				final_map[i][j] = Cells::Empty;
				break;

			case '#':
				final_map[i][j] = Cells::Wall;
				break;
			case 'P':
				pacman.set_position(cell_size * j, cell_size * i);
				break;
			case '1':
				ghost.set_position(cell_size * j, cell_size * i);
				break;
			case '.':
				final_map[i][j] = Cells::Food;
				break;
			case 'o':
				final_map[i][j] = Cells::Berries;
				break;
			case '=':
				final_map[i][j] = Cells::Door;
			}
		}
	}

	return final_map;
}