#pragma once

#include <array>
#include <iostream>

#include "Pacman.h"
#include "Ghost.h"
#include "Globals.h"

std::array<std::array<Cells, map_width>, map_height> convert_map(std::array<std::string, map_height> map, Pacman& pacman, std::array<Position, 4>& ghost_positions);