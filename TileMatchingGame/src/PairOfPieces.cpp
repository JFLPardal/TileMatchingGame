#include "pch.h"
#include "PairOfPieces.h"

#include "Piece.h"
#include "Renderer.h"
#include "EventHandler.h"
#include "PairPosition.h"

PairOfPieces::PairOfPieces()
{
	for (auto& piece : m_pair)
		piece = std::make_unique<Piece>();

	m_pair.at(1)->SetAsSecondInPair();
	m_pairPosition = PairPosition(*m_pair.at(0), *m_pair.at(1));

	EventHandler::SubscribeToEvent(SDL_KEYDOWN, 
				std::function<void(SDL_Event&)>(std::bind(&PairOfPieces::MovePairToTheSide, this, std::placeholders::_1)));
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

void PairOfPieces::MovePairToTheSide(SDL_Event& aEvent)
{
	if (m_inputEnabled)
	{
		auto keyPressed = aEvent.key.keysym.sym;
		if (keyPressed == SDL_KeyCode::SDLK_a)
		{
			if (CanMoveLeft())
				for (auto& piece : m_pair)
					piece->Move(MoveDirection::left);// UpdateX(-Consts::PIECE_W);
		}
		else if (keyPressed == SDL_KeyCode::SDLK_d)
		{
			if(CanMoveRight())
				for (auto& piece : m_pair)
					piece->Move(MoveDirection::right);
		}
	}
}

bool PairOfPieces::CanMoveRight() const
{
	const auto rightMostPieceX = (m_pairPosition.FirstPiecePos().X() > m_pairPosition.SecondPiecePos().X()) ?
								m_pairPosition.FirstPiecePos().X() :
								m_pairPosition.SecondPiecePos().X();
	return (rightMostPieceX + Consts::PIECE_W < Consts::GRID_FINAL_X);
}

bool PairOfPieces::CanMoveLeft() const
{
	const auto leftMostPieceX = (m_pairPosition.FirstPiecePos().X() > m_pairPosition.SecondPiecePos().X()) ? 
								m_pairPosition.SecondPiecePos().X() :
								m_pairPosition.FirstPiecePos().X();
	return (leftMostPieceX - Consts::PIECE_W >= Consts::GRID_INIT_X);
}

// needed on the cpp because of the forward decl of Piece
PairOfPieces::~PairOfPieces() = default;