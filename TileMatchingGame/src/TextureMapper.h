#pragma once
#include <map>
#include "Enums.h"
#include "Constants.h"
#include "Vector2.h"

std::map<const PieceColor, const Vector2> colorToTextureCoords =
{
	{PieceColor::brown, Vector2(Consts::TEX_BROWN_W, Consts::TEX_BROWN_H) },
	{PieceColor::red, Vector2(Consts::TEX_RED_W, Consts::TEX_RED_H) },
	{PieceColor::blue, Vector2(Consts::TEX_BLUE_W, Consts::TEX_BLUE_H) },
	{PieceColor::green, Vector2(Consts::TEX_GREEN_W, Consts::TEX_GREEN_H) }
};
