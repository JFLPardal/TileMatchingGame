#pragma once
#include "Constants.h"
#include "Vector2.h"

/*
	GridDataStructure encapsulates how the grid is represented
*/

class Piece;
class ColumnAvailability;
class Renderer;

class GridDataStructure
{
public:
	GridDataStructure();
	void Init();

	void Draw(Renderer* aRenderer, const Vector2& gridVisualStartingPoint) const;

	size_t GetColumnSize() { return m_grid.at(0).size(); }
	void AddPieceToGrid(std::unique_ptr<Piece> pieceToAdd, const Vector2& positionInGridIndex);

	std::vector<Vector2> GetAdjacentPositions(const Vector2& gridPosition) const;
	const Piece* const GetPieceInIndex(const Vector2& gridIndex) const { return m_grid.at(gridIndex.X()).at(gridIndex.Y()).get(); }
	const Piece* const GetPieceInIndex(int x, int y) const { return GetPieceInIndex(Vector2(x, y)); }
	void FindGroupsInGrid(ColumnAvailability* columnAvailability);
private:
	void DeleteGroupFromGrid(std::set<Vector2>& solution, ColumnAvailability* columnAvailability);
	void SettleSuspendedPieces();

	std::array<std::array<std::unique_ptr<Piece>, Consts::NUM_PIECES_H>, Consts::NUM_PIECES_W> m_grid;
	int e_groupSize = 0; // this needs to exist because of complications with the lifetime of data of user created events. A better solution should be found
};