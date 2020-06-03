#pragma once

namespace Consts
{
	// window properties
	constexpr char WINDOW_NAME[] = "Task 4 - Joao Pardal";
	constexpr int WINDOW_W = 768;
	constexpr int WINDOW_H = 1024;

	// game over text
	const std::string LEVEL_COMPLETED_TEXT	= "Level Completed!";
	const std::string GAME_LOST_TEXT		= "Game Lost";
	const std::string CURRENT_LEVEL_TEXT	= "Current Level: ";
	
	// text properties
	constexpr char FONT_PATH[]		= "assets\\Amatic.ttf";
	constexpr int TEXT_POINTS_SMALL = 20;
	constexpr int TEXT_POINTS_BIG	= 128;
	constexpr SDL_Color TEXT_COLOR_DEFAULT{0, 209, 209}; 
	constexpr SDL_Color TEXT_COLOR_GAME_LOST{209, 0, 0}; 

	// text position and dimensions
	constexpr int TEXT_W = WINDOW_W * .7f;
	constexpr int TEXT_H = 100;
	constexpr int TEXT_INITIAL_X = Consts::WINDOW_W * .5f - TEXT_W * .5f;
	constexpr int TEXT_INITIAL_Y = Consts::WINDOW_H * .4f;

	// UI bar dimensions
	constexpr int UI_BAR_W = 300;
	constexpr int UI_BAR_H = 40;

	// UI bar texture coords (regarding the 'tilesheet.png' texture)
	constexpr int UI_BAR_BACKGROUND_X = 11;
	constexpr int UI_BAR_BACKGROUND_Y = 6;

	constexpr int MIN_NUMBER_OF_PIECES_TO_MAKE_GROUP = 4;
	
	// progression and game over
	constexpr int POINTS_TO_CLEAR_1ST_LVL	= 20;
	constexpr int POINTS_TO_CLEAR_LVL_INC	= 60; 
	constexpr int MS_TO_LOSE_GAME			= 50 * 1000; 

	// pair and piece speed
	constexpr float PAIR_SPEED_BOOST	= 2.5f; // percentage that should be applied to the regular speed of a pair when the speed boost key is pressed
	constexpr float PIECE_DEFAULT_SPEED = 0.2f;

	// piece dimensions
	constexpr int PIECE_W = 48;
	constexpr int PIECE_H = 48;

	// texture dimensions
	constexpr int TEX_TILE_W = 64;
	constexpr int TEX_TILE_H = 64;

	// texture coordenates for each piece color
	constexpr int NUM_PIECE_COLORS	= 4;
	constexpr int TEX_BROWN_W		= 64;
	constexpr int TEX_BROWN_H		= 0;
	constexpr int TEX_RED_W			= 128;
	constexpr int TEX_RED_H			= 0;
	constexpr int TEX_BLUE_W		= 192;
	constexpr int TEX_BLUE_H		= 0;
	constexpr int TEX_GREEN_W		= 256;
	constexpr int TEX_GREEN_H		= 0;

	// these values avoid division at runtime when converting from screenPosition to gridIndex
	constexpr float STOG_W = 1 / static_cast<float>(PIECE_W);
	constexpr float STOG_H = 1 / static_cast<float>(PIECE_H);

	// number of pieces that the grid has
	constexpr int NUM_PIECES_W = 8;
	constexpr int NUM_PIECES_H = 16 + 1; // the extra line is used for the lose condition
	
	// pair move increment
	constexpr int MOVE_INCREMENT = PIECE_W;

	// grid starting pos
	constexpr int GRID_INIT_X = WINDOW_W * 0.5f - PIECE_W * (NUM_PIECES_W * 0.5f);
	constexpr int GRID_INIT_Y = WINDOW_H * 0.15f;

	//grid final pos
	constexpr int GRID_RIGHTMOST_X	= GRID_INIT_X + NUM_PIECES_W * PIECE_W;
	constexpr int GRID_BOTTOMMOST_Y = NUM_PIECES_H * PIECE_H + GRID_INIT_Y;
	
	// pair starting pos
	constexpr int PAIR_INIT_X = GRID_INIT_X + (NUM_PIECES_W * 0.5f - 1)* PIECE_W;
	constexpr int PAIR_INIT_Y = GRID_INIT_Y - PIECE_H;
	
	// next pairs to spawn 
	constexpr int NEXT_PAIR_TO_SPAWN_INIT_X = .6f * WINDOW_W;
	constexpr int NEXT_PAIR_TO_SPAWN_INIT_Y = .05f * WINDOW_H;
	constexpr int NUM_PAIRS_TO_SHOW = 1;	// needed a some non trivial work to put more than 1 pair at the same time being displayed in different positions on the screen without compromising the integraty of 'PairOfPieces' class. 
											// This number can be changed and it will break nothing, but the pair being shown on screen is not the next pair,
											// it's the (NUM_PAIRS_TO_SHOW-1)-th pair after the next one

	// framerate
	constexpr int INTENDED_FPS = 60;
	constexpr Uint32 INTENDED_FRAME_DURATION = 1000 / INTENDED_FPS;
}
