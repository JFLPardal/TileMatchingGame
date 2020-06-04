#include "pch.h"
#include "MatrixGrid.h"

#include "Piece.h"
#include "Wrappers/Renderer.h"
#include "PairOfPieces.h"
#include "Utils.h"
#include "ColumnAvailability.h"
#include "GridDataStructure.h"

MatrixGrid::MatrixGrid()
	: m_grid(std::make_unique<GridDataStructure>())
	, m_columnAvailability(std::make_unique<ColumnAvailability>())
{
	m_columnAvailability->InitColumnAvailability(m_grid->GetColumnSize() - 1);
	m_grid->Init();
}

bool MatrixGrid::IsDoneProcessingGroups()
{
	if (m_isDoneProcessingGroups)
	{
		m_isDoneProcessingGroups = false;
		return true;
	}
	return false;
}

bool MatrixGrid::IsFreeInPosition(const PairPosition& aScreenPos) const
{
	return aScreenPos.FirstPiecePos().Y() < m_columnAvailability->AvailableLineForColumn(aScreenPos.FirstPiecePos().X()) 
		&& aScreenPos.SecondPiecePos().Y() < m_columnAvailability->AvailableLineForColumn(aScreenPos.SecondPiecePos().X());
}

void MatrixGrid::TransferPairOwnershipToGrid(std::unique_ptr<PairOfPieces> pieceToAdd)
{
	m_lastPairAddedToGrid = std::move(pieceToAdd);
	m_lastPairAddedToGrid->DisableInput();
}

void MatrixGrid::Draw(Renderer* aRenderer) const
{
	m_grid->Draw(aRenderer, m_visualStartingPoint);
	if (m_lastPairAddedToGrid != nullptr) m_lastPairAddedToGrid->Draw(aRenderer);
}

void MatrixGrid::Update(int msSinceLastUpdate)
{
	static bool firstPieceHasSettled = false;
	static bool secondPieceHasSettled = false;
	static bool bothPiecesSettled = false;

  if (bothPiecesSettled)
  {
    m_grid->FindGroupsInGrid(m_columnAvailability.get());
    m_isDoneProcessingGroups = true;
    bothPiecesSettled = false;
  }
  else
  {
    UpdatePiecesUntilSettled(firstPieceHasSettled, secondPieceHasSettled, bothPiecesSettled, msSinceLastUpdate);
  }
}

void MatrixGrid::UpdatePiecesUntilSettled(bool& firstPieceHasSettled, bool& secondPieceHasSettled, bool& bothPiecesSettled, int msSinceLastUpdate)
{
	if (m_lastPairAddedToGrid->IsVertical())
	{
		const auto bottomPiece = (m_lastPairAddedToGrid->GetFirstPiecePos().Y() > m_lastPairAddedToGrid->GetSecondPiecePos().Y()) ?
								m_lastPairAddedToGrid->GetFirstPiecePos() :
								m_lastPairAddedToGrid->GetSecondPiecePos();

		bool bottomPieceHasSettled = m_columnAvailability->CheckIfPieceHasSettled(bottomPiece);
		if (bottomPieceHasSettled)
		{
			UpdateGridAndColumnAvailability();
			bothPiecesSettled = true;
			m_lastPairAddedToGrid = nullptr;
		}
		else
		{
			m_lastPairAddedToGrid->Update(msSinceLastUpdate, PairAcessPiece::both);
		}
	}
	else
	{
		firstPieceHasSettled = m_columnAvailability->CheckIfPieceHasSettled(m_lastPairAddedToGrid->GetFirstPiecePos());
		secondPieceHasSettled = m_columnAvailability->CheckIfPieceHasSettled(m_lastPairAddedToGrid->GetSecondPiecePos());

		if (firstPieceHasSettled && secondPieceHasSettled)
		{
			UpdateGridAndColumnAvailability();
			bothPiecesSettled = true;
			m_lastPairAddedToGrid = nullptr;
		}
		else if (firstPieceHasSettled) //update second piece
		{
			m_lastPairAddedToGrid->Update(msSinceLastUpdate, PairAcessPiece::second);
			if (m_columnAvailability->CheckIfPieceHasSettled(m_lastPairAddedToGrid->GetSecondPiecePos()))
			{
				UpdateGridAndColumnAvailability();
				bothPiecesSettled = true;
				m_lastPairAddedToGrid = nullptr;
			}
		}
		else if (secondPieceHasSettled) // update first piece
		{
			m_lastPairAddedToGrid->Update(msSinceLastUpdate, PairAcessPiece::first);
			if (m_columnAvailability->CheckIfPieceHasSettled(m_lastPairAddedToGrid->GetFirstPiecePos()))
			{
				UpdateGridAndColumnAvailability();
				bothPiecesSettled = true;
				m_lastPairAddedToGrid = nullptr;
			}
		}
	}
}

void MatrixGrid::UpdateGridAndColumnAvailability()
{
	const auto firstPiecePositionInGrid  = ScreenToGridPosition(m_lastPairAddedToGrid->GetFirstPiecePos());
	const auto secondPiecePositionInGrid = ScreenToGridPosition(m_lastPairAddedToGrid->GetSecondPiecePos());

	m_grid->AddPieceToGrid(m_lastPairAddedToGrid->AddFirstPieceToBoard(), firstPiecePositionInGrid);
	m_grid->AddPieceToGrid(m_lastPairAddedToGrid->AddSecondPieceToBoard(), secondPiecePositionInGrid);
	
	// updated column availability
	m_columnAvailability->IncreaseColumnHeight(firstPiecePositionInGrid);
	m_columnAvailability->IncreaseColumnHeight(secondPiecePositionInGrid);
}

// needed on the cpp because of the forward decl of Piece
MatrixGrid::~MatrixGrid() = default;