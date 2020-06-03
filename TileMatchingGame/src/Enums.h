#pragma once

enum class UserEventType : Sint32
{
	notDefined,
	groupDestroyed,
	ranOutOfGridSpace,
	pointsUpdated,
	pointsForLevelReached,
	UIElementCreated,
	UIElementDestroyed,
	newFrame,
	timeRanOut,
	pairOfPiecesDestroyed,
	newPairOfPiecesActive,
	movePairWithKeyboard,
	rotatePairWithMouse
};

enum class DefaultEventType : Sint32
{
	userEvent	= SDL_USEREVENT,
	quit		= SDL_QUIT,
	keyDown		= SDL_KEYDOWN,
	mouseButtonDown = SDL_MOUSEBUTTONDOWN
};

enum class KeyboardKey : Uint8
{
	s = SDLK_s,
	a = SDLK_a,
	d = SDLK_d
};

enum class MouseButton
{
	left	= SDL_BUTTON_LEFT,
	right	= SDL_BUTTON_RIGHT
};

enum class RestartCondition
{
	levelCompleted,
	levelFailed
};

enum class CoordToConvert
{
	x, 
	y
};

enum class CoordToResize
{
	x,
	y
};

enum class PairAcessPiece
{
	first,
	second,
	both
};

enum class MoveDirection
{
	left,
	right,
	down,
	up
};

enum class PieceColor
{
	brown,
	red,
	blue,
	green
};

enum class ColumnHeightModifier
{
	increase,
	decrease
};

enum class FontSize
{
	small,
	big
};
