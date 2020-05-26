#include "pch.h"
#include "Vector2.h"

Vector2::Vector2()
	:Vector2(0,0)
{
}

Vector2::Vector2(int aX, int aY)
	:m_x(aX) , m_y(aY)
{
}

Vector2::Vector2(int aSingleValue)
	:Vector2(aSingleValue, aSingleValue)
{
}

Vector2::Vector2(const Vector2& vectorToCopy)
{
	m_x = vectorToCopy.m_x;
	m_y = vectorToCopy.m_y;
}

bool Vector2::operator==(const Vector2& vector1) const
{
	return m_x == vector1.m_x && m_y == vector1.m_y;
}

bool operator<(const Vector2& vector1, const Vector2& vector2) 
{
	if (vector2.m_y == vector1.m_y)
		return vector2.m_x > vector1.m_x;
	else 
		return vector2.m_y > vector1.m_y;
}