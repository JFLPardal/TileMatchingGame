#pragma once

#include "IGridRepresentation.h"
#include "Constants.h"
#include "Vector2.h"

/*
	MatrixGrid has operations that the matrix needs to do but it is
	independent of the matrix representation method,
	The methods that are representation dependent are on 'GridDataStructure' (should be an interface instead)
*/

class PairOfPieces;
class ColumnAvailability;
class PairPosition;
class GridDataStructure;

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
	void UpdatePiecesUntilSettled(bool& firstPieceHasSettled, bool& secondPieceHasSettled, bool& bothPiecesSettled, int msSinceLastUpdate);
	void UpdateGridAndColumnAvailability();
	
	bool m_isDoneProcessingGroups = true;
	std::unique_ptr<PairOfPieces> m_lastPairAddedToGrid{ nullptr };

	std::unique_ptr<GridDataStructure> m_grid;
	std::unique_ptr<ColumnAvailability> m_columnAvailability;
};