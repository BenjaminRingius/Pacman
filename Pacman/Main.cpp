#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

#include "Globals.h"
#include "ConvertMap.h"
#include "drawMap.h"
#include "Node_Management.h"

int main() {

    std::array<std::string, map_height> map = {
        "###################",
        "#........#........#",
        "#.##.###.#.###.##.#",
        "#o##.###.#.###.##o#",
        "#.................#",
        "#.##.#.#####.#.##.#",
        "#....#...#...#....#",
        "####.### # ###.####",
        "   #.#   1   #.#   ",
        "####.# ##=## #.####",
        "    .  #   #  .    ",
        "####.# ##### #.####",
        "   #.#       #.#   ",
        "####.# ##### #.####",
        "#........#........#",
        "#.##.###.#.###.##.#",
        "#o.#.....P.....#.o#",
        "##.#.#.#####.#.#.##",
        "#....#...#...#....#",
        "#.######.#.######.#",
        "#.................#",
        "###################"
    };

    Pacman pacman;

    Ghosts ghost;

    std::array<std::array<Cells, map_width>, map_height> converted_map = convert_map(map, pacman, ghost);

    std::vector<std::vector<short>> nodes = point_out_nodes(converted_map);

    sf::RenderWindow window(sf::VideoMode(map_width*cell_size, map_height * cell_size), "Pacman");
    window.setFramerateLimit(100);

    sf::Event events;
    while (1 == window.isOpen()) {

        while (window.pollEvent(events)) {

            if (events.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        draw_map(converted_map, window);
        ghost.draw(window);
        pacman.draw(window);
        pacman.update(converted_map);
        ghost.update(converted_map, pacman, nodes);
        pacman.direction_management(converted_map, nodes);
        window.display();
    }

    return 0;
}