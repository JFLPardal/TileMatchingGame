#pragma once
#include "Vector2.h"
#include "Enums.h"

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

	void Move(MoveDirection directionToMove);

	const Vector2& GetScreenPos() const { return m_screenPosition; }
	Rect* GetTextureRect() const { return m_textureRect.get(); }

	void SetAsSecondInPair();
private:
	std::unique_ptr<Rect> m_textureRect{ nullptr };
	Vector2 m_screenPosition;
};
