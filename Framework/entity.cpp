
// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"
#include "game.h"

// Library includes:
#include <cassert>
#include <cmath>

Entity::Entity()
: m_pSprite(0)
, m_x(0)
, m_y(0)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
{

}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;
	return (true);
}

void Entity::Process(float deltaTime)
{
	// Generic position update, based upon velocity (and time).
	m_x += (m_velocityX * deltaTime);
	m_y += (m_velocityY * deltaTime);

	// Boundary checking and position capping. 
	if (m_x > Game::SCREEN_WIDTH - m_pSprite->GetWidth()) 
	{
		m_x = (float) Game::SCREEN_WIDTH - m_pSprite->GetWidth();
	} 
	else if (m_x < 0) 
	{
		m_x = 0;
	}

	if (m_y > Game::SCREEN_HEIGHT - m_pSprite->GetWidth())
	{
		m_y = (float)Game::SCREEN_HEIGHT - m_pSprite->GetWidth();
	}
	else if (m_y < 0)
	{
		m_y = 0;
	}
}

void Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->Draw(backBuffer);
}

bool Entity::IsCollidingWith(Entity* e, float distance)
{
	// Generic Entity Collision routine.

	float distanceBetweenEntities = 0;
	distanceBetweenEntities = 
		std::sqrt(pow(e->GetPositionX() - GetPositionX(), 2) 
		+ pow(e->GetPositionY() - GetPositionY(), 2))
		- e->m_pSprite->GetWidth() - m_pSprite->GetWidth();

	return distanceBetweenEntities < distance;
}

void Entity::SetDead(bool dead)
{
	m_dead = dead;
}

bool Entity::IsDead() const
{
	return m_dead;
}

void Entity::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

float 
Entity::GetPositionX() const
{
	return (m_x);
}

float 
Entity::GetPositionY() const
{
	return (m_y);
}

float 
Entity::GetHorizontalVelocity() const
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity() const
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}
