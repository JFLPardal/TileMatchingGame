#pragma once

#include "IGridRepresentation.h"
#include "Constants.h"

/*
	MatrixGrid represents the grid as a matrix (array of arrays)
*/

class Piece;

class MatrixGrid : public IGridRepresentation
{
public:
	MatrixGrid();
	~MatrixGrid();
private:
	void InitGrid();

	std::array<std::array<std::unique_ptr<Piece>, Consts::GRID_H>, Consts::GRID_W> m_grid;
};