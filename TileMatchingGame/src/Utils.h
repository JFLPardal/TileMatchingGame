#pragma once
#include "Enums.h"

class Vector2;

Vector2 ScreenToGridPosition(const Vector2& aScreenPosition);

int ScreenToGridPositon(int aValue, CoordToConvert aCoordToConvert);
