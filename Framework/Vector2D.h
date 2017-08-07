#pragma once

#ifndef ___VECTOR_2D_H___
#define ___VECTOR_2D_H___

class Vector2D
{
	float m_x;
	float m_y;
public:
	float getLength();
	static float dot(float a, float b);
};

#endif // ___VECTOR_2D_H___