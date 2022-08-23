#pragma once

#include <array>
#include <iostream>

#include "Pacman.h"
#include "Ghosts.h"
#include "Globals.h"

std::array<std::array<Cells, map_width>, map_height> convert_map(std::array<std::string,map_height> map, Pacman& pacman, Ghosts& ghost);