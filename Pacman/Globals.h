#pragma once

constexpr char map_height = 22;
constexpr char map_width = 19;

constexpr short cell_size = 36;
constexpr short pac_speed = 4;

constexpr char pac_anime_speed = 5;
constexpr char pac_anime_frames = 4;

constexpr char ghost_anime_speed = 8;
constexpr char ghost_anime_frames = 2;

constexpr short ghost_speed = 4;

enum class Cells {
	Empty,
	Wall,
	Food,
	Berries,
	Door,
};

struct Position {
	short x; short y;
};