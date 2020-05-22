#include "pch.h"
#include "MatrixGrid.h"

#include "Piece.h"
#include "Renderer.h"
#include "PairOfPieces.h"
#include "Utils.h"

MatrixGrid::MatrixGrid()
{
	InitGrid();
}

void MatrixGrid::InitGrid()
{
	for (auto& column : m_grid)
		for (auto& piece : column)
			piece = nullptr; //std::make_unique<Piece>();//nullptr;

}

void MatrixGrid::AddPieceToGrid(std::unique_ptr<PairOfPieces> pieceToAdd)
{
	// calculate grid position based on screen position (?) use another more efficient way that was implemented
	Vector2 pieceGridPosition = ScreenToGridPosition(pieceToAdd->GetScreenPos());
	m_grid.at(pieceGridPosition.X()).at(pieceGridPosition.Y()) = pieceToAdd->AddFirstPieceToBoard();
	m_grid.at(pieceGridPosition.X() + 1).at(pieceGridPosition.Y()) = pieceToAdd->AddSecondPieceToBoard();
}

void MatrixGrid::Draw(Renderer* renderer)
{
	for (auto x = 0; x < m_grid.size(); x++)
	{
		for (auto y = 0; y < m_grid.at(x).size(); y++)
		{
			if (m_grid.at(x).at(y) != nullptr)
			{
				renderer->Draw(m_grid.at(x).at(y)->GetTextureRect(),
					m_visualStartingPoint.X() + x * Consts::PIECE_W,
					m_visualStartingPoint.Y() + y * Consts::PIECE_H);
			}
		}
	}
}

// needed on the cpp because of the forward decl of Piece
MatrixGrid::~MatrixGrid() = default;
