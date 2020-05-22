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
