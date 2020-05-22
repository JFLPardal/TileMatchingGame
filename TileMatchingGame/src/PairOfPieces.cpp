#include "pch.h"
#include "PairOfPieces.h"

#include "Piece.h"
#include "Renderer.h"

PairOfPieces::PairOfPieces()
{
	for (auto& piece : m_pair)
		piece = std::make_unique<Piece>();
	for (auto i = 0; i < m_screenPositions.size(); i++)
		m_screenPositions.at(i) = Vector2(Consts::PAIR_INIT_X + i * Consts::PIECE_W, Consts::PAIR_INIT_Y);
	
	static int spawned = 0;
	if (spawned <= 2)
	{
		for (auto i = 0; i < m_screenPositions.size(); i++)
			m_screenPositions.at(i).UpdateX(spawned * Consts::PIECE_W);
		spawned++;
	}
}

void PairOfPieces::Update(Uint32 aMsSinceLastUpdate)
{
	for (auto i = 0; i < m_screenPositions.size(); i++)
		m_screenPositions.at(i).UpdateY(.25f * aMsSinceLastUpdate);
}

void PairOfPieces::Draw(Renderer* aRenderer)
{
	for (auto i = 0; i < m_screenPositions.size(); i++)
		aRenderer->Draw(m_pair.at(i)->GetTextureRect(), m_screenPositions.at(i));
}

std::unique_ptr<Piece> PairOfPieces::AddFirstPieceToBoard()
{
	return std::move(m_pair.at(0));
}

std::unique_ptr<Piece> PairOfPieces::AddSecondPieceToBoard()
{
	return std::move(m_pair.at(1));
}

// needed on the cpp because of the forward decl of Piece
PairOfPieces::~PairOfPieces() = default;