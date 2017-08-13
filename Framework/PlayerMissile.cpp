#include "PlayerMissile.h"
#include "entity.h"
#include "sprite.h"

#include <cmath>

PlayerMissile::PlayerMissile()
	: m_age(0),
	m_explode(false)
{
	Entity::Entity();
}

PlayerMissile::PlayerMissile(float startX, float endX, float startY, float endY)
	: m_age(0),
	m_explode(false)
{
	m_startX = startX;
	m_startY = startY;
	m_endX = endX;
	m_endY = endY;

	PlayerMissile::Entity();
}

PlayerMissile::~PlayerMissile()
{
	Entity::~Entity();
}

void PlayerMissile::Process(float deltaTime)
{
	m_age += deltaTime;

	m_x = Lerp(m_startX, m_endX, m_age);
	m_y = Lerp(m_startY, m_endY, m_age);

	if (m_age >= m_detonationAge)
	{
		m_explode = true;
	}

	Entity::Process(deltaTime);
}

bool PlayerMissile::IsCollidingWith(Entity * e)
{
	return Entity::IsCollidingWith(e, 25.0f);
}

float PlayerMissile::Lerp(float start, float end, float time)
{
	time = time / m_detonationAge; // Take 3 seconds
	return (((1 - time) * start) + (time * end));
}
