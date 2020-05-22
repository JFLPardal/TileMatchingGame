#pragma once
#include "Vector2.h"
#include "Constants.h"

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

	void Update(Uint32 msSinceLastUpdate);
	void Draw(Renderer* renderer);

	inline const Vector2& GetScreenPos() { return m_ScreenPosition; }

	std::unique_ptr<Piece> AddFirstPieceToBoard();
	std::unique_ptr<Piece> AddSecondPieceToBoard();
private:
	std::array<std::unique_ptr<Piece>, 2> m_pair;
	Vector2 m_ScreenPosition{ Consts::PAIR_INIT_X, Consts::PAIR_INIT_Y };
};