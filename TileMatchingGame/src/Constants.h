#pragma once

namespace Consts
{
	// piece dimensions
	constexpr int PIECE_W = 48;
	constexpr int PIECE_H = 48;

	// texture dimensions
	constexpr int TEX_TILE_W = 64;
	constexpr int TEX_TILE_H = 64;

	// these values avoid division at runtime when converting from screenPosition to gridIndex
	constexpr float STOG_W = 1 / static_cast<float>(PIECE_W);
	constexpr float STOG_H = 1 / static_cast<float>(PIECE_H);

	// window properties
	constexpr char WINDOW_NAME[] = "Task 4 - Joao Pardal";
	constexpr int WINDOW_W = 768;
	constexpr int WINDOW_H = 1024;

	// number of pieces that the grid has
	constexpr int NUM_PIECES_W = 8;
	constexpr int NUM_PIECES_H = 16;
	
	// grid starting pos
	constexpr int GRID_INIT_X = WINDOW_W * 0.5f - PIECE_W * (NUM_PIECES_W * 0.5f);
	constexpr int GRID_INIT_Y = WINDOW_H * 0.15f;

	//grid additional
	constexpr int GRID_BOTTOM_POS = NUM_PIECES_H * PIECE_H + GRID_INIT_Y;
	
	// pair starting pos
	constexpr int PAIR_INIT_X = GRID_INIT_X + (NUM_PIECES_W * 0.5f - 1)* PIECE_W;
	//constexpr int PAIR_INIT_X = GRID_INIT_X + (NUM_PIECES_W * 0.5f - 3)* PIECE_W;
	constexpr int PAIR_INIT_Y = GRID_INIT_Y;
	
	// framerate
	constexpr int INTENDED_FPS = 60;
	constexpr Uint32 INTENDED_FRAME_DURATION = 1000 / INTENDED_FPS;
}
