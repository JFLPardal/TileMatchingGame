#pragma once

enum class UserEventType : Sint32
{
	groupDestroyed,
	levelCompleted,
	levelFailed
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
