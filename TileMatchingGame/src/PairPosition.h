#pragma once

/*
	PairPosition is as abstraction
	of the position of the pieces in a pair
*/

class Vector2;
class Piece;

class PairPosition
{
public:
	PairPosition();
	PairPosition( Piece& piece1,  Piece& piece2);

	const Vector2& FirstPiecePos() const { return *m_pairPosition.at(0); }
	const Vector2& SecondPiecePos() const { return *m_pairPosition.at(1); }
private:
	std::array<const Vector2*, 2> m_pairPosition;
};