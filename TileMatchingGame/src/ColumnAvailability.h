#pragma once
#include "Constants.h"

/*
	ColumnAvailability is responsible for keeping
	track of the topmost available tile for each of the
	columns in MatrixGrid
*/

class Vector2;

class ColumnAvailability
{
public:
	ColumnAvailability() = default;

	void InitColumnAvailability(unsigned int columnSize);
	int AvailableLineForColumn(int aXInScreenPos);
	void UpdateColumnAvailability(const Vector2& columnToUpdate);
	bool CheckIfPieceReachedColumnTop(const Vector2& pieceScreenPosition);
private:
	std::array<unsigned short, Consts::NUM_PIECES_W> m_columnAvailability;
};