#pragma once
#include "Vector2.h"
#include "Enums.h"
#include "Constants.h"

/*
	Piece represents (...)
*/
class Rect;
class Renderer;

class Piece
{
public:
	Piece();
	~Piece();

	void Update(int msSinceLastUpdate);
	void Draw(Renderer* aRenderer);

	// this function increments the current position, to move the piece to a specific position use MoveTo
	void Move(MoveDirection directionToMove);
	// this function overrides the previous position, to increment the current position use Move
	void MoveTo(const Vector2& screenPosToMoveTo);

	const Vector2& GetScreenPos() const { return m_screenPosition; }
	Rect* GetTextureRect() const { return m_textureRect.get(); }
	PieceColor GetColor() const { return m_color;  }

	void SetAsSecondInPair();
private:
	void AssignColorAndTexture();

	std::unique_ptr<Rect> m_textureRect{ nullptr };
	Vector2 m_screenPosition;
	PieceColor m_color;
};
