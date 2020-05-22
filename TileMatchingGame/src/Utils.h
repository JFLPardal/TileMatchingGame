#pragma once
#include "pch.h"
#include "Vector2.h"

Vector2 ScreenToGridPosition(const Vector2& aScreenPosition)
{
	Vector2 gridIndexes;
	gridIndexes.SetX(static_cast<int>(std::floorf((aScreenPosition.X() - Consts::GRID_INIT_X) * Consts::STOG_W)));
	gridIndexes.SetY(static_cast<int>(std::floorf((aScreenPosition.Y() - Consts::GRID_INIT_Y) * Consts::STOG_H)));
	return gridIndexes;
}
