#pragma once

/*
	Piece represents (...)
*/
class Rect;

class Piece
{
public:
	Piece();
	~Piece();

	Rect* GetTextureRect() const { return m_textureRect.get(); }
private:
	std::unique_ptr<Rect> m_textureRect{ nullptr };
};
