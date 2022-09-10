#include "drawMap.h"


void draw_map(std::array<std::array<Cells, map_width>, map_height>& map, sf::RenderWindow& window) {

	sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));

	sf::RectangleShape food(sf::Vector2f(cell_size / 6, cell_size / 6));
	sf::CircleShape berry(cell_size / 4);

	food.setFillColor(sf::Color::White);
	food.setOrigin(0 - food.getLocalBounds().width * 3 + 1, 0 - food.getLocalBounds().height * 3 + 1);
	berry.setFillColor(sf::Color::White);
	berry.setOrigin(0 - berry.getLocalBounds().width / 2, 0 - berry.getLocalBounds().height / 2);

	for (char i = 0; i < map_height; i++) {

		for (char j = 0; j < map_width; j++) {

			cell.setPosition(cell_size * j, cell_size * i);

			switch (map[i][j]) {
			case Cells::Wall:
				cell.setFillColor(sf::Color(36, 36, 255));
				window.draw(cell);
				break;
			case Cells::Door:
				cell.setFillColor(sf::Color(186, 186, 200));
				window.draw(cell);
				break;
			case Cells::Food:
				food.setPosition(cell_size * j, cell_size * i);
				window.draw(food);
				break;
			case Cells::Berries:
				berry.setPosition(cell_size * j, cell_size * i);
				window.draw(berry);
			}

		}
	}
}