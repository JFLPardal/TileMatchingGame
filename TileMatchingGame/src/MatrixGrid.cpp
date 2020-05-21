#include "pch.h"
#include "MatrixGrid.h"

#include "Piece.h"
#include "Renderer.h"

MatrixGrid::MatrixGrid()
{
	InitGrid();
}

void MatrixGrid::InitGrid()
{
	for (auto& column : m_grid)
		for (auto& piece : column)
			piece = std::make_unique<Piece>();//nullptr;
}


void MatrixGrid::Draw(Renderer* renderer)
{
	int x = 0, y = 0;
	for (auto& column : m_grid)
	{
		for (auto& piece : column)
		{
			renderer->Draw(piece.get()->GetTextureRect(), x, y); // TODO CHANGE THESE VALUES
			y += Consts::PIECE_H;
		}
		y = 0;
		x += Consts::PIECE_W;
	}
}

// needed on the cpp because of the forward decl of Piece
MatrixGrid::~MatrixGrid() = default;
