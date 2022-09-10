#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

#include "Globals.h"
#include "ConvertMap.h"
#include "drawMap.h"
#include "Node_Management.h"
#include "Ghosts.h"
#include "GhostManager.h"

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
        "   #.#   0123#.#   ",
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

    GhostManager ghost_manager;

    std::array<Position, 4> ghost_positions;

    std::array<std::array<Cells, map_width>, map_height> converted_map = convert_map(map, pacman, ghost_positions);

    std::vector<std::vector<short>> nodes = point_out_nodes(converted_map);

    ghost_manager.reset(ghost_positions);

    sf::RenderWindow window(sf::VideoMode(map_width * cell_size, map_height * cell_size), "Pacman");
    window.setFramerateLimit(60);

    sf::Event events;
    while (1 == window.isOpen()) {

        while (window.pollEvent(events)) {

            if (events.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        draw_map(converted_map, window);
        ghost_manager.draw(window);
        pacman.draw(window);
        pacman.update(converted_map);
        ghost_manager.update(converted_map, pacman, nodes);
        pacman.direction_management(converted_map, nodes);
        window.display();
    }

    return 0;
}