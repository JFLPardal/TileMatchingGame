#include "pch.h"
#include "Piece.h"
#include "Constants.h"
#include "Utils.h"

#include "Rect.h"
#include "Renderer.h"
#include "TextureMapper.h"

Piece::Piece()
{
	m_screenPosition = Vector2(Consts::NEXT_PAIR_TO_SPAWN_INIT_X, Consts::NEXT_PAIR_TO_SPAWN_INIT_Y);
	AssignColorAndTexture();
}

void Piece::AssignColorAndTexture()
{
	m_color = static_cast<PieceColor>(rand() % Consts::NUM_PIECE_COLORS);
	const auto textureCoords = colorToTextureCoords.at(m_color);
	m_textureRect = std::make_unique<Rect>(textureCoords.X(), textureCoords.Y(),
											Consts::TEX_TILE_W, Consts::TEX_TILE_H);
}

void Piece::Update(int aMsSinceLastUpdate)
{
	m_screenPosition.UpdateY(Consts::PIECE_DEFAULT_SPEED * aMsSinceLastUpdate);
}

void Piece::Draw(Renderer* aRenderer)
{
	aRenderer->Draw(GetTextureRect(), m_screenPosition);
}

void Piece::Move(MoveDirection directionToMove)
{
	if(directionToMove == MoveDirection::left)		 m_screenPosition.UpdateX(-Consts::MOVE_INCREMENT);
	else if(directionToMove == MoveDirection::right) m_screenPosition.UpdateX(Consts::MOVE_INCREMENT);
	else if(directionToMove == MoveDirection::down)  m_screenPosition.UpdateY(Consts::MOVE_INCREMENT);
	else if(directionToMove == MoveDirection::up)    m_screenPosition.UpdateY(-Consts::MOVE_INCREMENT);
}

void Piece::MoveTo(const Vector2& screenPosToMoveTo)
{
	m_screenPosition.SetX(screenPosToMoveTo.X());
	m_screenPosition.SetY(screenPosToMoveTo.Y());
}

void Piece::SetAsSecondInPair()
{
	// this increments the second piece's x one piece to the right side
	m_screenPosition.UpdateX(Consts::PIECE_W);
}

// needed on the cpp because of the forward decl of Rect
Piece::~Piece() = default;
