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
class PairPosition; 
class ColumnAvailability;

class IGridRepresentation
{
public:
	virtual void Draw(Renderer* renderer) const = 0;
	virtual void Update(int msSinceLastUpdate) = 0;

	virtual bool LastPairHasBeenPlacedInGrid() = 0;

	virtual bool IsFreeInPosition(const PairPosition& screenPos) const = 0;
	virtual void TransferPairOwnershipToGrid(std::unique_ptr<PairOfPieces> pieceToAdd) = 0;
	virtual const ColumnAvailability* const GetColumnAvailability() const = 0;

	virtual ~IGridRepresentation() {};
protected:

	Vector2 m_visualStartingPoint{Consts::GRID_INIT_X, Consts::GRID_INIT_Y };
};