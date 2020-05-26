#pragma once

#include "IGridRepresentation.h"
#include "Constants.h"
#include "Vector2.h"

/*
	MatrixGrid represents the grid as a matrix (array of arrays)
*/

class PairOfPieces;
class ColumnAvailability;
class PairPosition;

class MatrixGrid : public IGridRepresentation
{
public:
	MatrixGrid();
	~MatrixGrid();

	void Draw(Renderer* renderer) const override;
	void Update(int msSinceLastUpdate) override;

	bool IsDoneProcessingGroups() override;

	void TransferPairOwnershipToGrid(std::unique_ptr<PairOfPieces> pieceToAdd) override;

	bool IsFreeInPosition(const PairPosition& screenPos) const override;
	const ColumnAvailability* const GetColumnAvailability() const override { return m_columnAvailability.get(); }
private:
	void InitGrid();

	bool FindGroupsInGrid();
	void UpdatePiecesUntilSettled(bool& firstPieceHasSettled, bool& secondPieceHasSettled, bool& bothPiecesSettled, int msSinceLastUpdate);
	void UpdateGridAndColumnAvailability();
	
	void DeleteGroupFromGrid(std::set<Vector2>& solution);
	void SettleSuspendedPieces();
	std::vector<Vector2> GetAdjacentPositions(const Vector2& gridPosition) const;
	const Piece* const GetPieceInIndex(const Vector2& gridIndex) const { return m_grid.at(gridIndex.X()).at(gridIndex.Y()).get(); }
	const Piece* const GetPieceInIndex(int x, int y) const { return GetPieceInIndex(Vector2(x,y)); }

	bool m_isDoneProcessingGroups = false;
	std::unique_ptr<PairOfPieces> m_lastPairAddedToGrid{ nullptr };

	std::array<std::array<std::unique_ptr<Piece>, Consts::NUM_PIECES_H>, Consts::NUM_PIECES_W> m_grid;
	std::unique_ptr<ColumnAvailability> m_columnAvailability;
};