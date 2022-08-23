#pragma once

#include <array>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Globals.h"


void draw_map(std::array<std::array<Cells, map_width>, map_height>& map, sf::RenderWindow& window);