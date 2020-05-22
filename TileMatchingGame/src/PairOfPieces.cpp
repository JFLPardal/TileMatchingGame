#include "pch.h"
#include "PairOfPieces.h"

#include "Piece.h"
#include "Renderer.h"

PairOfPieces::PairOfPieces()
{
	for (auto& piece : m_pair)
		piece = std::make_unique<Piece>();
}

// needed on the cpp because of the forward decl of Piece
PairOfPieces::~PairOfPieces() = default;

void PairOfPieces::Update(Uint32 aMsSinceLastUpdate)
{
	m_ScreenPosition.UpdateY(.25f * aMsSinceLastUpdate);
}

void PairOfPieces::Draw(Renderer* aRenderer)
{
	for(auto& piece : m_pair)
		aRenderer->Draw(piece->GetTextureRect(), m_ScreenPosition);
}

std::unique_ptr<Piece> PairOfPieces::AddFirstPieceToBoard()
{
	return std::move(m_pair.at(0));
}

std::unique_ptr<Piece> PairOfPieces::AddSecondPieceToBoard()
{
	return std::move(m_pair.at(1));
}
