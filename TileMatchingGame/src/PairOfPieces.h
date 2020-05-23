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

class PairOfPieces
{
public:
	PairOfPieces();
	~PairOfPieces();

	void Update(Uint32 msSinceLastUpdate, PairAcessPiece pieceToUpdate = PairAcessPiece::both);
	void Draw(Renderer* renderer);

	const PairPosition& GetScreenPos() const;
	const Vector2& GetFirstPiecePos() const;
	const Vector2& GetSecondPiecePos() const;

	std::unique_ptr<Piece> AddFirstPieceToBoard();
	std::unique_ptr<Piece> AddSecondPieceToBoard();
private:
	std::array<std::unique_ptr<Piece>, 2> m_pair;
	PairPosition m_pairPosition;
};