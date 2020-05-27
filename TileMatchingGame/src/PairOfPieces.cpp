#include "pch.h"
#include "PairOfPieces.h"

#include "Piece.h"
#include "Renderer.h"
#include "EventHandler.h"
#include "PairPosition.h"
#include "ColumnAvailability.h"

PairOfPieces::PairOfPieces(const ColumnAvailability* columnAvailability)
{
	for (auto& piece : m_pair)
		piece = std::make_unique<Piece>();

	m_pair.at(1)->SetAsSecondInPair();
	m_pairPosition = PairPosition(*m_pair.at(0), *m_pair.at(1));

	EventHandler::SubscribeToEvent(SDL_KEYDOWN, 
							std::function<void(SDL_Event&)>(std::bind(&PairOfPieces::MovePairToTheSide, this, std::placeholders::_1)));

	EventHandler::SubscribeToEvent(SDL_MOUSEBUTTONDOWN,
							std::function<void(SDL_Event&)>(std::bind(&PairOfPieces::RotatePair, this, std::placeholders::_1)));

	m_columnAvailability = columnAvailability;
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
					piece->Move(MoveDirection::left);
		}
		else if (keyPressed == SDL_KeyCode::SDLK_d)
		{
			if(CanMoveRight())
				for (auto& piece : m_pair)
					piece->Move(MoveDirection::right);
		}
	}
}

void PairOfPieces::RotatePair(SDL_Event& event)
{
	const auto deltaPairPosition = m_pairPosition.SecondPiecePos() - m_pairPosition.FirstPiecePos();
	bool secondPieceIsToTheRight = deltaPairPosition.X() > 0;
	bool secondPieceIsBelow		 = deltaPairPosition.Y() > 0;

	bool rotateClockwise = event.button.button == SDL_BUTTON_LEFT;

	const auto& firstPiece = m_pair.at(0).get();
	const auto& secondPiece = m_pair.at(1).get();

	if (deltaPairPosition.X() == 0)
	{
		if (((secondPieceIsBelow && rotateClockwise) || (!secondPieceIsBelow && !rotateClockwise)))
		{
			if (secondPiece->GetScreenPos().X() > Consts::GRID_INIT_X 
				&& (m_columnAvailability->AvailableLineForColumn(secondPiece->GetScreenPos().X() - Consts::PIECE_W))  > secondPiece->GetScreenPos().Y())
			{
				secondPiece->MoveTo(Vector2(firstPiece->GetScreenPos().X() - Consts::PIECE_W, firstPiece->GetScreenPos().Y()));
				m_isVertical = false;
			}
			else return;
		}
		else if ((!secondPieceIsBelow && rotateClockwise) || (secondPieceIsBelow && !rotateClockwise))
		{
			if (secondPiece->GetScreenPos().X() + Consts::PIECE_W < Consts::GRID_RIGHTMOST_X
				&& (m_columnAvailability->AvailableLineForColumn(secondPiece->GetScreenPos().X() + Consts::PIECE_W)) > m_pair.at(0)->GetScreenPos().Y())
			{
				secondPiece->MoveTo(Vector2(firstPiece->GetScreenPos().X() + Consts::PIECE_W, firstPiece->GetScreenPos().Y()));
				m_isVertical = false;
			}
			else return;
		}
	}
	else if (deltaPairPosition.Y() == 0)
	{
		if ((secondPieceIsToTheRight && rotateClockwise) || (!secondPieceIsToTheRight && !rotateClockwise))
		{
			if (secondPiece->GetScreenPos().Y() + Consts::PIECE_H < Consts::GRID_BOTTOMMOST_Y
				&& (m_columnAvailability->AvailableLineForColumn(secondPiece->GetScreenPos().X()) > secondPiece->GetScreenPos().Y() + Consts::PIECE_H))
			{
				secondPiece->MoveTo(Vector2(firstPiece->GetScreenPos().X(), firstPiece->GetScreenPos().Y() + Consts::PIECE_H)); 
				m_isVertical = true;
			}
			else return;
		}
		else if (deltaPairPosition.Y() == 0 && ((!secondPieceIsToTheRight && rotateClockwise) || (secondPieceIsToTheRight && !rotateClockwise)))
		{
			if (secondPiece->GetScreenPos().Y() + Consts::PIECE_H > Consts::GRID_INIT_Y)
			{
				secondPiece->MoveTo(Vector2(firstPiece->GetScreenPos().X(), firstPiece->GetScreenPos().Y() - Consts::PIECE_H));
				m_isVertical = true;
			}
			else return;
		}
	}
}

bool PairOfPieces::CanMoveRight() const
{
	const auto rightMostPiece = (m_pairPosition.FirstPiecePos().X() > m_pairPosition.SecondPiecePos().X()) ?
								m_pairPosition.FirstPiecePos() :
								m_pairPosition.SecondPiecePos();

	bool attemptedMoveIsInsideGrid = rightMostPiece.X() + Consts::PIECE_W < Consts::GRID_RIGHTMOST_X;
	if (attemptedMoveIsInsideGrid)
	{
		return CanMoveToColumnToTheSide(rightMostPiece, MoveDirection::right);
	}
	return false;
}

bool PairOfPieces::CanMoveLeft() const
{
	const auto leftMostPiece = (m_pairPosition.FirstPiecePos().X() > m_pairPosition.SecondPiecePos().X()) ? 
								m_pairPosition.SecondPiecePos():
								m_pairPosition.FirstPiecePos() ;
	
	bool attemptedMoveIsInsideGrid = leftMostPiece.X() - Consts::PIECE_W >= Consts::GRID_INIT_X;
	if (attemptedMoveIsInsideGrid)
	{
		return CanMoveToColumnToTheSide(leftMostPiece, MoveDirection::left);
	}
	return false;
}

// PieceToCheck is the position of the right or leftmost piece for the pair. 
// The one to use is the same as the direction of the attempted move
bool PairOfPieces::CanMoveToColumnToTheSide(const Vector2& aPieceToCheck, MoveDirection aNewColumn) const
{
	int availableHeightOfColumnToMoveTo = -1;

	if(aNewColumn == MoveDirection::left)
		availableHeightOfColumnToMoveTo = m_columnAvailability->AvailableLineForColumn(aPieceToCheck.X() - Consts::PIECE_W);
	else
		availableHeightOfColumnToMoveTo = m_columnAvailability->AvailableLineForColumn(aPieceToCheck.X() + Consts::PIECE_W);
	
	if (availableHeightOfColumnToMoveTo < aPieceToCheck.Y())
		return false;
	return true;
}

// needed on the cpp because of the forward decl of Piece
PairOfPieces::~PairOfPieces() = default;