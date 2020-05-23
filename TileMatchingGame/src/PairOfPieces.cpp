#include "pch.h"
#include "PairOfPieces.h"

#include "Piece.h"
#include "Renderer.h"
#include "EventHandler.h"

PairOfPieces::PairOfPieces()
	:m_pairPosition(PairPosition(*m_pair.at(0), *m_pair.at(1)))
{
	for (auto& piece : m_pair)
		piece = std::make_unique<Piece>();
	m_pair.at(1)->SetAsSecondInPair();

	// TODO add the const to Piece::GetScreenPos()
	static int pairsSpawned = 0;
	if (pairsSpawned <= 2)
	{
		m_pair.at(0)->UpdateX(Consts::PIECE_W * pairsSpawned);
		m_pair.at(1)->UpdateX(Consts::PIECE_W * pairsSpawned);
	}
	else if(pairsSpawned <= 4)
	{
		m_pair.at(0)->UpdateX(-Consts::PIECE_W* (pairsSpawned-3));
		m_pair.at(1)->UpdateX(-Consts::PIECE_W* (pairsSpawned-3));
	}
	pairsSpawned++;
	/////////////////////////////////////

	m_pairPosition = PairPosition(*m_pair.at(0), *m_pair.at(1));
	EventHandler::SubscribeToEvent(SDL_KEYDOWN, 
				std::function<void(void*, void*)>(std::bind(&PairOfPieces::MovePairToTheSide, this, std::placeholders::_1, std::placeholders::_2)));
}

void PairOfPieces::Update(Uint32 aMsSinceLastUpdate, PairAcessPiece aPieceToUpdate)
{
	switch (aPieceToUpdate)
	{
	case PairAcessPiece::first:
		m_pair.at(0)->Update(aMsSinceLastUpdate);
		break;
	case PairAcessPiece::second:
		m_pair.at(1)->Update(aMsSinceLastUpdate);
		break;
	case PairAcessPiece::both:
		for (auto& piece : m_pair)
			piece->Update(aMsSinceLastUpdate);
		break;
	}
}

void PairOfPieces::Draw(Renderer* aRenderer)
{
	for (auto& piece : m_pair)
		piece->Draw(aRenderer);
}

const Vector2& PairOfPieces::GetFirstPiecePos() const
{
	return m_pairPosition.FirstPiecePos();
}

const Vector2& PairOfPieces::GetSecondPiecePos() const
{
	return m_pairPosition.SecondPiecePos();
}

const PairPosition& PairOfPieces::GetScreenPos() const
{
	return m_pairPosition;
}

std::unique_ptr<Piece> PairOfPieces::AddFirstPieceToBoard()
{
	return std::move(m_pair.at(0));
}

std::unique_ptr<Piece> PairOfPieces::AddSecondPieceToBoard()
{
	return std::move(m_pair.at(1));
}

void PairOfPieces::MovePairToTheSide(void* a, void* b)
{
	if (m_inputEnabled)
	{
		auto keyPressed = static_cast<SDL_KeyCode*>(a);
		if (*keyPressed == SDL_KeyCode::SDLK_a)
		{
			for (auto& piece : m_pair)
				piece->UpdateX(-Consts::PIECE_W);
		}
		else if (*keyPressed == SDL_KeyCode::SDLK_d)
		{
			for (auto& piece : m_pair)
				piece->UpdateX(Consts::PIECE_W);
		}
	}
}

// needed on the cpp because of the forward decl of Piece
PairOfPieces::~PairOfPieces() = default;