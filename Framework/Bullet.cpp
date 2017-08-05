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

void Bullet::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}