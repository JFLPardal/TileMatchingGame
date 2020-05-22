#include "pch.h"
#include "ColumnAvailability.h"

#include "Utils.h"
#include "Vector2.h"

void ColumnAvailability::InitColumnAvailability(unsigned int aColumnSize)
{
	for (auto& columnAvailability : m_columnAvailability)
		columnAvailability = aColumnSize;
}

int ColumnAvailability::AvailableLineForColumn(int aXInScreenPos)
{
	int xInGridIndex = ScreenToGridPositon(aXInScreenPos, CoordToConvert::x);
	return Consts::GRID_INIT_Y + Consts::PIECE_H * m_columnAvailability.at(xInGridIndex);
}

void ColumnAvailability::UpdateColumnAvailability(const Vector2& columnToUpdate)
{
	m_columnAvailability.at(columnToUpdate.X())--;
	m_columnAvailability.at(columnToUpdate.X() + 1)--;
}
