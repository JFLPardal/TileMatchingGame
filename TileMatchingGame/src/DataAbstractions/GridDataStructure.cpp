#include "pch.h"
#include "GridDataStructure.h"

#include "Vector2.h"
#include "Enums.h"
#include "Piece.h"
#include "Events/UserEvent.h"
#include "Wrappers/Renderer.h"
#include "ColumnAvailability.h"

GridDataStructure::GridDataStructure()
{
}

void GridDataStructure::Init()
{
	for (auto& column : m_grid)
		for (auto& piece : column)
			piece = nullptr;
}

void GridDataStructure::Draw(Renderer* aRenderer, const Vector2& gridVisualStartingPoint) const
{
	for (auto x = 0; x < m_grid.size(); x++)
	{
		for (auto y = 0; y < m_grid.at(x).size(); y++)
		{
			if (GetPieceInIndex(x, y) != nullptr)
			{
				aRenderer->DrawPiece(GetPieceInIndex(x, y)->GetTextureRect(),
					gridVisualStartingPoint.X() + x * Consts::PIECE_W,
					gridVisualStartingPoint.Y() + y * Consts::PIECE_H);
			}
		}
	}
}

void GridDataStructure::FindGroupsInGrid(ColumnAvailability* aColumnAvailability)
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
				if (solution.size() >= Consts::MIN_NUMBER_OF_PIECES_TO_MAKE_GROUP)
				{
					DeleteGroupFromGrid(solution, aColumnAvailability);
					SettleSuspendedPieces();
				}
			}
		}
	}
}

void GridDataStructure::DeleteGroupFromGrid(std::set<Vector2>& solution, ColumnAvailability* aColumnAvailability)
{
	for (auto& position : solution)
	{
		m_grid.at(position.X()).at(position.Y()).reset(nullptr);
		aColumnAvailability->DecreaseColumnHeight(position);
	}

	e_groupSize = solution.size();
	UserEvent(UserEventType::groupDestroyed, &e_groupSize);
}

void GridDataStructure::SettleSuspendedPieces()
{
	for (auto x = 0; x < m_grid.size(); x++)
		for (int y = m_grid.at(x).size() - 2; y >= 0; y--) // processing will be done bottom up, -2 because there is no need to check the bottommost line
		{
			if (GetPieceInIndex(x, y) != nullptr)
			{
				int yBelow = y + 1;
				while (yBelow < Consts::NUM_PIECES_H
					&& GetPieceInIndex(x, yBelow) == nullptr)
				{
					m_grid.at(x).at(yBelow).reset(m_grid.at(x).at(yBelow - 1).release());
					yBelow++;
				}
			}
		}
}

void GridDataStructure::AddPieceToGrid(std::unique_ptr<Piece> aPieceToAdd, const Vector2& aPositionInGridIndex)
{
	m_grid.at(aPositionInGridIndex.X()).at(aPositionInGridIndex.Y()) = std::move(aPieceToAdd);
}

std::vector<Vector2> GridDataStructure::GetAdjacentPositions(const Vector2& gridPosition) const
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
