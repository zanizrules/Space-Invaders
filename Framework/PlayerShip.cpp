#include "PlayerShip.h"
#include "entity.h"

PlayerShip::PlayerShip()
{
	Entity::Entity();
}

PlayerShip::~PlayerShip()
{
	Entity::~Entity();
}

void PlayerShip::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}
