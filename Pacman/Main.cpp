#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

#include "Globals.h"
#include "ConvertMap.h"
#include "drawMap.h"
#include "Node_Management.h"
#include "Ghost.h"
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
        "   #.#   0   #.#   ",
        "####.# ##=## #.####",
        "    .  #123#  .    ",
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
    window.setFramerateLimit(50);

    bool filled_screen = 0;

    sf::Event events;
    while (1 == window.isOpen()) {

        while (window.pollEvent(events)) {

            if (events.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && 1 != filled_screen) {
                filled_screen = 1;
                window.create(sf::VideoMode(map_width * cell_size + 768, map_height * cell_size), "Pacman");
                window.setFramerateLimit(50);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && 0 != filled_screen) {
                filled_screen = 0;
                window.create(sf::VideoMode(map_width * cell_size, map_height * cell_size), "Pacman");
                window.setFramerateLimit(50);
            }
        }

        window.clear(sf::Color::Black);

        draw_map(converted_map, window);
        ghost_manager.draw(window);
        pacman.draw(window);
        pacman.update(converted_map);

        if (1 == pacman.start_game()) {

            if (1 == ghost_manager.update(converted_map, pacman, nodes)) { // When this update returns 1 it means that we have a collision between pacman and a ghost or if pacman wins
                ghost_manager.reset(ghost_positions);
                converted_map = convert_map(map, pacman, ghost_positions); // when we reset this converted_map array it'll set the start position for pacman and the ghosts
            }
        }

        pacman.direction_management(converted_map, nodes);
        window.display();
    }

    return 0;
}