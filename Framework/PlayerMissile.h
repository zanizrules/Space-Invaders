#pragma once

#ifndef ___PLAYER_MISSILE_H___
#define ___PLAYER_MISSILE_H___

#include "entity.h"

class PlayerMissile : public Entity
{
public:
	PlayerMissile();
	PlayerMissile(float startX, float endX, float startY, float endY);
	~PlayerMissile();

	void Process(float deltaTime);

	bool IsCollidingWith(Entity * e);

	float Lerp(float start, float end, float time);

	const float m_detonationAge = 3.0f;
	float m_startX;
	float m_startY;
	float m_endX;
	float m_endY;
	float m_age;
	bool m_explode;

private:
};

#endif // ___PLAYER_MISSILE_H___