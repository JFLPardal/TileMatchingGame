#include "pch.h"
#include "Piece.h"
#include "Constants.h"

#include "Rect.h"
#include "Renderer.h"

Piece::Piece()
	:m_textureRect(std::make_unique<Rect>(64, 0, Consts::TEX_TILE_W, Consts::TEX_TILE_H))
{
	m_screenPosition = Vector2(Consts::PAIR_INIT_X, Consts::PAIR_INIT_Y);
}

void Piece::Update(int aMsSinceLastUpdate)
{
	m_screenPosition.UpdateY(.25f * aMsSinceLastUpdate);
}

void Piece::Draw(Renderer* aRenderer)
{
	aRenderer->Draw(GetTextureRect(), m_screenPosition);
}

void Piece::SetAsSecondInPair()
{
	// this increments the second piece's x one piece to the right side
	m_screenPosition.UpdateX(Consts::PIECE_W);
}

// needed on the cpp because of the forward decl of Rect
Piece::~Piece() = default;
