#include "Vector2D.h"
#include <math.h>

float Vector2D::getLength()
{
	return sqrt(pow(m_x, 2) + pow(m_y, 2));
}

float Vector2D::dot(float a, float b)
{
	return 0.0f;
}

void Vector2D::Add(float x, float y)
{
	m_x += x;
	m_y += y;
}

void Vector2D::Clear()
{
	m_x = 0;
	m_y = 0;
}
