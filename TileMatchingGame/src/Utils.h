#pragma once
#include "Enums.h"
#include "Constants.h"

class Vector2;

Vector2 ScreenToGridPosition(const Vector2& aScreenPosition);

int ScreenToGridPositon(int aValue, CoordToConvert aCoordToConvert);

void Delay(Uint32 msToDelay);