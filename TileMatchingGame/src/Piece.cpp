#include "pch.h"
#include "Piece.h"

Piece::Piece()
{
	static int x = 0;
	printf("created piece %d\n", x);
	x++;
}
