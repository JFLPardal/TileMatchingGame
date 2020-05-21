#pragma once

namespace Consts
{
	// piece dimensions
	constexpr int PIECE_W = 48;
	constexpr int PIECE_H = 48;

	// texture dimensions
	constexpr int TEX_TILE_W = 64;
	constexpr int TEX_TILE_H = 64;

	// grid dimensions
	constexpr int GRID_W = 8;
	constexpr int GRID_H = 16;

	// window properties
	constexpr char WINDOW_NAME[] = "Task 4 Joao Pardal";
	constexpr int WINDOW_W = 768;
	constexpr int WINDOW_H = 1024;

	// framerate
	constexpr int INTENDED_FPS = 60;
	constexpr Uint32 INTENDED_FRAME_DURATION = 1000 / INTENDED_FPS;
}
