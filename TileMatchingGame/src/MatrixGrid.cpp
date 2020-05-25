#include "pch.h"
#include "MatrixGrid.h"

#include "Piece.h"
#include "Renderer.h"
#include "PairOfPieces.h"
#include "Utils.h"
#include "ColumnAvailability.h"

MatrixGrid::MatrixGrid()
	: m_columnAvailability(std::make_unique< ColumnAvailability>())
{
	m_columnAvailability->InitColumnAvailability(m_grid.at(0).size() - 1);
	InitGrid();
}

void MatrixGrid::InitGrid()
{
	for (auto& column : m_grid)
		for (auto& piece : column)
			piece = nullptr;
	m_grid.at(3).at(15) = std::make_unique<Piece>();
	m_grid.at(4).at(15) = std::make_unique<Piece>();
	m_grid.at(3).at(14) = std::make_unique<Piece>();
	m_grid.at(4).at(14) = std::make_unique<Piece>();
	m_grid.at(3).at(13) = std::make_unique<Piece>();
	m_grid.at(4).at(13) = std::make_unique<Piece>();
	m_columnAvailability->UpdateColumnAvailability(Vector2(3,1));
	m_columnAvailability->UpdateColumnAvailability(Vector2(3,1));
	m_columnAvailability->UpdateColumnAvailability(Vector2(3,1));
	m_columnAvailability->UpdateColumnAvailability(Vector2(4,1));
	m_columnAvailability->UpdateColumnAvailability(Vector2(4,1));
	m_columnAvailability->UpdateColumnAvailability(Vector2(4,1));
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
	for (auto x = 0; x < m_grid.size(); x++)
	{
		for (auto y = 0; y < m_grid.at(x).size(); y++)
		{
			if (m_grid.at(x).at(y) != nullptr)
			{
				aRenderer->Draw(m_grid.at(x).at(y)->GetTextureRect(),
					m_visualStartingPoint.X() + x * Consts::PIECE_W,
					m_visualStartingPoint.Y() + y * Consts::PIECE_H);
			}
		}
	}
	if (m_lastPairAddedToGrid != nullptr) m_lastPairAddedToGrid->Draw(aRenderer);
}

void MatrixGrid::Update(int msSinceLastUpdate)
{
	static bool firstPieceHasSettled = false;
	static bool secondPieceHasSettled = false;
	static bool bothPiecesSettled = false;

	if (bothPiecesSettled)
	{
		m_isDoneProcessingGroups = FindGroupsInGrid();
		if (m_isDoneProcessingGroups)
			bothPiecesSettled = false;
	}
	else
	{
		UpdatePiecesUntilSettled(firstPieceHasSettled, secondPieceHasSettled, bothPiecesSettled, msSinceLastUpdate);
	}
}

void MatrixGrid::UpdatePiecesUntilSettled(bool& firstPieceHasSettled, bool& secondPieceHasSettled, bool& bothPiecesSettled, int msSinceLastUpdate)
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

void MatrixGrid::UpdateGridAndColumnAvailability()
{
	const auto firstPiecePositionInGrid  = ScreenToGridPosition(m_lastPairAddedToGrid->GetFirstPiecePos());
	const auto secondPiecePositionInGrid = ScreenToGridPosition(m_lastPairAddedToGrid->GetSecondPiecePos());

	// add pieces the grid
	m_grid.at(firstPiecePositionInGrid.X()).at(firstPiecePositionInGrid.Y())   = m_lastPairAddedToGrid->AddFirstPieceToBoard();
	m_grid.at(secondPiecePositionInGrid.X()).at(secondPiecePositionInGrid.Y()) = m_lastPairAddedToGrid->AddSecondPieceToBoard();
	
	// updated column availability
	m_columnAvailability->UpdateColumnAvailability(firstPiecePositionInGrid);
	m_columnAvailability->UpdateColumnAvailability(secondPiecePositionInGrid);
}

bool MatrixGrid::FindGroupsInGrid()
{
	return true;
}

// needed on the cpp because of the forward decl of Piece
MatrixGrid::~MatrixGrid() = default;
