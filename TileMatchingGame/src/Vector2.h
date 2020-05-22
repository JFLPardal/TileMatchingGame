#pragma once

/*
	Vector2 represents a point along with some
	point operations
*/

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	Vector2(int singleValue);

	inline int X() const { return m_x; }
	inline int Y() const { return m_y; }
	
	// this adds the increment to the current x, use SetX to reset
	inline void UpdateX(int xIncrement) { m_x += xIncrement; }
	// this adds the increment to the current y, use SetY to reset
	inline void UpdateY(int yIncrement) { m_y += yIncrement; }
	// this resets the current value of x, to add to it, use UpdateX
	inline void SetX(int newX) { m_x = newX; }
	// this resets the current value of y, to add to it, use UpdateY
	inline void SetY(int newY) { m_y  = newY; }
private:
	int m_x, m_y;
};
