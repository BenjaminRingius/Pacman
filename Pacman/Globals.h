#pragma once

constexpr char map_height = 22;
constexpr char map_width = 19;

constexpr short cell_size = 32;
constexpr short pac_speed = 2;

constexpr char pac_anime_speed = 7;
constexpr char pac_anime_frames = 4;

constexpr short ghost_speed = 2;

enum class Cells { // I use enum class over enum because the compiler doesn't like it, nothing dangerous or something that cause an error.
	Empty,
	Wall,
	Food,
	Berries,
	Door,
};

struct Position {
	short x; short y;
};