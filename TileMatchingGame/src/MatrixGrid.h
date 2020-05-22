#pragma once

#include "IGridRepresentation.h"
#include "Constants.h"

/*
	MatrixGrid represents the grid as a matrix (array of arrays)
*/

class PairOfPieces;
class ColumnAvailability;

class MatrixGrid : public IGridRepresentation
{
public:
	MatrixGrid();
	~MatrixGrid();

	void Draw(Renderer* renderer) const override;
	void Update(std::unique_ptr<PairOfPieces> pieceToAdd) override;

	bool IsFreeInPosition(const Vector2& screenPos) const override;
private:
	void InitGrid();

	void AddPieceToGrid(std::unique_ptr<PairOfPieces> pieceToAdd) override;

	std::array<std::array<std::unique_ptr<Piece>, Consts::NUM_PIECES_H>, Consts::NUM_PIECES_W> m_grid;
	std::unique_ptr<ColumnAvailability> m_columnAvailability;
};