#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

#include "Globals.h"
#include "Pacman.h"


bool map_collision(short x, short y, std::array<std::array<Cells, map_width>, map_height>& map, bool isPacman);