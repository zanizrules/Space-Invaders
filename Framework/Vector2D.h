#pragma once

#ifndef ___VECTOR_2D_H___
#define ___VECTOR_2D_H___

class Vector2D
{

public:
	float m_x;
	float m_y;

	float getLength();
	static float dot(float a, float b);
	void Add(float x, float y);
	void Clear();
};

#endif // ___VECTOR_2D_H___