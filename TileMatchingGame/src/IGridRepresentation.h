#pragma once
#include "Vector2.h"
#include "Constants.h"

/*
	IGridRepresentation defines all the functions any 
	implementation of Grid should provide
*/

class Renderer;
class Piece;
class PairOfPieces;

class IGridRepresentation
{
public:
	virtual void Draw(Renderer* renderer) const = 0;
	virtual void Update(std::unique_ptr<PairOfPieces> pieceToAdd) = 0;

	virtual bool IsFreeInPosition(const Vector2& screenPos) const = 0;

	virtual ~IGridRepresentation() {};
protected:
	virtual void AddPieceToGrid(std::unique_ptr<PairOfPieces> pieceToAdd) = 0;

	Vector2 m_visualStartingPoint{Consts::GRID_INIT_X, Consts::GRID_INIT_Y };
};