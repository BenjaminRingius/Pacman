#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>

#include "Globals.h"

std::vector<std::vector<short>> point_out_nodes(std::array<std::array<Cells, map_width>, map_height>& map);