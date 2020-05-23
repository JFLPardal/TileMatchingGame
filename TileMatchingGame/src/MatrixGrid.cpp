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
	InitGrid();
	m_columnAvailability->InitColumnAvailability(m_grid.at(0).size() - 1);
}

void MatrixGrid::InitGrid()
{
	for (auto& column : m_grid)
		for (auto& piece : column)
			piece = nullptr; //std::make_unique<Piece>();//nullptr;
}

bool MatrixGrid::LastPairHasBeenPlacedInGrid()
{
	if (m_lastPairHasBeenPlaced)
	{
		m_lastPairHasBeenPlaced = false;
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
	static bool firstPieceReachedColumnTop = true, secondPieceReachedColumnTop = true;

	firstPieceReachedColumnTop = m_columnAvailability->CheckIfPieceReachedColumnTop(m_lastPairAddedToGrid->GetFirstPiecePos());
	secondPieceReachedColumnTop = m_columnAvailability->CheckIfPieceReachedColumnTop(m_lastPairAddedToGrid->GetSecondPiecePos());
	
	if (firstPieceReachedColumnTop && secondPieceReachedColumnTop)
	{
		UpdateGridAndColumnAvailability();
		m_lastPairHasBeenPlaced = true;
		m_lastPairAddedToGrid = nullptr;
	}
	else if (firstPieceReachedColumnTop) //update second piece
	{
		m_lastPairAddedToGrid->Update(msSinceLastUpdate, PairAcessPiece::second);
		if (m_columnAvailability->CheckIfPieceReachedColumnTop(m_lastPairAddedToGrid->GetSecondPiecePos()))
		{
			UpdateGridAndColumnAvailability();
			m_lastPairHasBeenPlaced = true;
			m_lastPairAddedToGrid = nullptr;
		}
	}
	else // update first piece
	{
		m_lastPairAddedToGrid->Update(msSinceLastUpdate, PairAcessPiece::first);
		if (m_columnAvailability->CheckIfPieceReachedColumnTop(m_lastPairAddedToGrid->GetFirstPiecePos()))
		{
			UpdateGridAndColumnAvailability();
			m_lastPairHasBeenPlaced = true;
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

// needed on the cpp because of the forward decl of Piece
MatrixGrid::~MatrixGrid() = default;
