#include "EnemyShip.h"
#include "entity.h"

EnemyShip::EnemyShip()
{
	Entity::Entity();
}

EnemyShip::~EnemyShip()
{
	Entity::~Entity();
}

void EnemyShip::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}

