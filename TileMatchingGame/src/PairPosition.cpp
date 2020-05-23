#include "pch.h"
#include "PairPosition.h"

#include "Vector2.h"
#include "Piece.h"


PairPosition::PairPosition()
{
	m_pairPosition.at(0) = nullptr;
	m_pairPosition.at(1) = nullptr;
}

PairPosition::PairPosition(Piece& piece1, Piece& piece2)
{
	m_pairPosition.at(0) = &piece1.GetScreenPos();
	m_pairPosition.at(1) = &piece2.GetScreenPos();
}
