#include "Bullet.h"
#include "entity.h"

Bullet::Bullet()
{
	Entity::Entity();
}

Bullet::~Bullet()
{
	Entity::~Entity();
}

bool Bullet::IsCollidingWith(Entity * e)
{
	return Entity::IsCollidingWith(e, 0);
}

void Bullet::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}

