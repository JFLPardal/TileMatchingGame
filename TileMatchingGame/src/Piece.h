#pragma once
#include "Vector2.h"

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

	// TODO delete this after 'automatic' positions in spawner is removed
	void UpdateX(int increment) { m_screenPosition.UpdateX(increment); }

	const Vector2& GetScreenPos() const { return m_screenPosition; }
	Rect* GetTextureRect() const { return m_textureRect.get(); }

	void SetAsSecondInPair();
private:
	std::unique_ptr<Rect> m_textureRect{ nullptr };
	Vector2 m_screenPosition;
};
