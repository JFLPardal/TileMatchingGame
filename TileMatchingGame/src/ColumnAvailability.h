#pragma once
#include "Constants.h"
#include "Enums.h"

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

	int AvailableLineForColumn(int aXInScreenPos) const;
	bool CheckIfPieceHasSettled(const Vector2& pieceScreenPosition) const;

	void IncreaseColumnHeight(const Vector2& columnToUpdate);
	void DecreaseColumnHeight(const Vector2& columnToUpdate);
private:
	void UpdateColumnAvailability(const Vector2& columnToUpdate, ColumnHeightModifier modifier);

	std::array<unsigned short, Consts::NUM_PIECES_W> m_columnAvailability;
};