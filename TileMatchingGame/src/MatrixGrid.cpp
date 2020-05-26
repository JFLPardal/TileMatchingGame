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
	/*m_grid.at(3).at(15) = std::make_unique<Piece>();
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
	m_columnAvailability->UpdateColumnAvailability(Vector2(4,1));*/
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
			if (GetPieceInIndex(x,y) != nullptr)
			{
				aRenderer->Draw(GetPieceInIndex(x, y)->GetTextureRect(),
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

// TODO
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
	for (auto i = 0; i < m_grid.size(); i++)
	{
		for (auto j = 0; j < m_grid.at(i).size(); j++)
		{
			Vector2 initialPos(i, j);
			if (GetPieceInIndex(initialPos) != nullptr)
			{

				std::set<Vector2> solution;
				std::set<Vector2> seen;
				std::deque<Vector2> toProcess;
			
				PieceColor currentColor = GetPieceInIndex(initialPos)->GetColor();

				toProcess.insert(toProcess.end(), initialPos);
				seen.insert(initialPos);

				while (!toProcess.empty())
				{
					Vector2 posBeingProcessed = toProcess.front();
					if (GetPieceInIndex(posBeingProcessed)->GetColor() == currentColor)
					{
						solution.insert(posBeingProcessed);
						std::vector<Vector2> adjacentPositions = GetAdjacentPositions(posBeingProcessed);
						for (auto& adjacentPosition : adjacentPositions)
						{
							if (seen.find(adjacentPosition) == seen.end())
							{
								toProcess.insert(toProcess.end(), adjacentPosition);
								seen.insert(adjacentPosition);
							}
						}
					}
					toProcess.pop_front();
				}
				if (solution.size() > 1)
				{
					printf("----solution------\n\n");
					for (auto& pos : solution)
					{
						printf("[%d, %d] \n", pos.X(), pos.Y());
					}
					printf("----end-----------\n\n");
				}
			}
		}
	}
	return true;
}

std::vector<Vector2> MatrixGrid::GetAdjacentPositions(const Vector2& gridPosition) const
{
	std::vector<Vector2> adjacentPositions;

	// process piece to the right
	Vector2 positionToTheRight(gridPosition);
	positionToTheRight.UpdateX(1);
	bool positionToTheRightIsValid = positionToTheRight.X() < Consts::NUM_PIECES_W
									 && GetPieceInIndex(positionToTheRight) != nullptr;

	if (positionToTheRightIsValid)
		adjacentPositions.insert(adjacentPositions.end(), positionToTheRight);

	// process piece to the left
	Vector2 positionToTheLeft(gridPosition);
	positionToTheLeft.UpdateX(-1);
	bool positionToTheLeftIsValid = positionToTheLeft.X() >= 0
									&& GetPieceInIndex(positionToTheLeft) != nullptr;

	if (positionToTheLeftIsValid)
		adjacentPositions.insert(adjacentPositions.end(), positionToTheLeft);

	// process piece above
	Vector2 positionAbove(gridPosition);
	positionAbove.UpdateY(-1);
	bool positionAboveIsValid = positionAbove.Y() >= 0
								&& GetPieceInIndex(positionAbove) != nullptr;
	if (positionAboveIsValid)
		adjacentPositions.insert(adjacentPositions.end(), positionAbove);

	// process piece below
	Vector2 positionBelow(gridPosition);
	positionBelow.UpdateY(1);
	bool positionBelowIsValid = positionBelow.Y() < Consts::NUM_PIECES_H
								&& GetPieceInIndex(positionBelow) != nullptr;
	if (positionBelowIsValid)
		adjacentPositions.insert(adjacentPositions.end(), positionBelow);

	return adjacentPositions;
}

// needed on the cpp because of the forward decl of Piece
MatrixGrid::~MatrixGrid() = default;