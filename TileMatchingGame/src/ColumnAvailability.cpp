#include "pch.h"
#include "ColumnAvailability.h"

#include "Utils.h"
#include "Vector2.h"
#include "UserEvent.h"

void ColumnAvailability::InitColumnAvailability(unsigned int aColumnSize)
{
	for (auto& columnAvailability : m_columnAvailability)
		columnAvailability = aColumnSize;
}

int ColumnAvailability::AvailableLineForColumn(int aXInScreenPos) const
{
	int xInGridIndex = ScreenToGridPositon(aXInScreenPos, CoordToConvert::x);
	return Consts::GRID_INIT_Y + Consts::PIECE_H * m_columnAvailability.at(xInGridIndex);
}

void ColumnAvailability::IncreaseColumnHeight(const Vector2& columnToUpdate)
{
	UpdateColumnAvailability(columnToUpdate, ColumnHeightModifier::increase);
}

void ColumnAvailability::DecreaseColumnHeight(const Vector2& columnToUpdate)
{
	UpdateColumnAvailability(columnToUpdate, ColumnHeightModifier::decrease);
}

void ColumnAvailability::UpdateColumnAvailability(const Vector2& columnToUpdate, ColumnHeightModifier modifier)
{
	if(modifier == ColumnHeightModifier::decrease) m_columnAvailability.at(columnToUpdate.X())++;
	if(modifier == ColumnHeightModifier::increase) m_columnAvailability.at(columnToUpdate.X())--;
}

bool ColumnAvailability::CheckIfPieceHasSettled(const Vector2& aPieceScreenPosition) const
{
	int yInGridIndex = ScreenToGridPositon(aPieceScreenPosition.Y(), CoordToConvert::y);
	auto availableLine = AvailableLineForColumn(aPieceScreenPosition.X());
	if (aPieceScreenPosition.Y() >= AvailableLineForColumn(aPieceScreenPosition.X()) && yInGridIndex == 0)
		UserEvent levelFailed(UserEventType::levelFailed);

	return aPieceScreenPosition.Y() >= AvailableLineForColumn(aPieceScreenPosition.X());
}
