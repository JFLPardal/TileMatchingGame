#include "pch.h"
#include "Piece.h"

#include "Constants.h"
#include "Rect.h"

Piece::Piece()
	:m_textureRect(std::make_unique<Rect>(64, 0, Consts::TEX_TILE_W, Consts::TEX_TILE_H))
{
	static int x = 0;
	printf("created piece %d\n", x);
	x++;
}

// needed on the cpp because of the forward decl of Rect
Piece::~Piece() = default;
