#include "pch.h"
#include "MatrixGrid.h"

#include "Piece.h"

MatrixGrid::MatrixGrid()
{
	InitGrid();
}

void MatrixGrid::InitGrid()
{
	for(auto& column : m_grid)
		for (auto& element : column)
			element = nullptr;
}

// needed on the cpp because of the forward decl of Piece
MatrixGrid::~MatrixGrid() = default;