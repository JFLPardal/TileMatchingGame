#pragma once
#include "Vector2.h"
#include "Constants.h"
#include "Enums.h"
#include "PairPosition.h"

/*
	PairOfPieces encapsulates a pair of pieces
	and its implementation. It also exposes the
	operations that can be done on a pair of pieces.
*/
class Piece;
class Renderer; 
class ColumnAvailability;
class IEventData;

class PairOfPieces
{
public:
	PairOfPieces(const ColumnAvailability* columnAvailability);
	~PairOfPieces();

	void Update(Uint32 msSinceLastUpdate, PairAcessPiece pieceToUpdate = PairAcessPiece::both);
	void Draw(Renderer* renderer);

	const PairPosition& GetScreenPos() const;
	const Vector2& GetFirstPiecePos() const;
	const Vector2& GetSecondPiecePos() const;
	// a pair is vertical if the pieces are on top of each other rather then side by side
	bool IsVertical() const { return m_isVertical; }

	std::unique_ptr<Piece> AddFirstPieceToBoard();
	std::unique_ptr<Piece> AddSecondPieceToBoard();

	void SetActive();
	void DisableInput() { m_inputEnabled = false; }
private:
	void MovePairToTheSide(IEventData& event);
	void RotatePair(IEventData& event);
	void CheckForSpeedBoost();

	bool CanMoveLeft() const;
	bool CanMoveToColumnToTheSide(const Vector2& leftMostPiece, MoveDirection newColumn) const;
	bool CanMoveRight() const;
	
	bool m_inputEnabled = true;
	float m_pieceSpeedPercentage = 1.f;
	bool m_isVertical = false;
	const ColumnAvailability* m_columnAvailability{ nullptr };
	std::array<std::unique_ptr<Piece>, 2> m_pair;
	PairPosition m_pairPosition;
};