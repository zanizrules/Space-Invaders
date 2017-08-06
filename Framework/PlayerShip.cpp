#include "PlayerShip.h"
#include "entity.h"
#include "game.h"
#include "sprite.h"

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

bool PlayerShip::Initialise(Sprite * sprite)
{
	Entity::Initialise(sprite);

	m_x = (float)(Game::SCREEN_WIDTH - m_pSprite->GetWidth()) / 2;
	m_y = (float) Game::SCREEN_HEIGHT - (2 * m_pSprite->GetHeight());

	return true;
}
