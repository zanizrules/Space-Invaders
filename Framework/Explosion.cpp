#include "Explosion.h"
#include "AnimatedSprite.h"
#include "backbuffer.h"

#include <cassert>

Explosion::Explosion()
: m_pAnimatedSprite(0)
, m_x(0)
, m_y(0)
, m_dead(false)
{
	
}

Explosion::~Explosion()
{
	delete m_pAnimatedSprite;
	m_pAnimatedSprite = 0;
}

void Explosion::Process(float deltaTime)
{
	if (!m_dead)
	{
		assert(m_pAnimatedSprite);
		m_pAnimatedSprite->Process(deltaTime);
		if (!m_pAnimatedSprite->IsAnimating())
		{
			m_dead = true;
		}
	}
}

bool Explosion::Initialise(AnimatedSprite* sprite)
{
	assert(sprite);
	if (m_pAnimatedSprite == 0)
	{
		m_pAnimatedSprite = sprite;
	}
	SetFrameSize(64, 64);
	SetAnimationSpeed(0.07f); // Delay between frames
	return true;
}

void Explosion::Draw(BackBuffer& backBuffer)
{
	assert(m_pAnimatedSprite);
	m_pAnimatedSprite->SetX(static_cast<int>(m_x));
	m_pAnimatedSprite->SetY(static_cast<int>(m_y));
	m_pAnimatedSprite->Draw(backBuffer);
}

void Explosion::SetDead(bool dead)
{
	m_dead = dead;
}

bool Explosion::IsDead() const
{
	return m_dead;
}

void Explosion::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void Explosion::SetPositionX(float x)
{
	m_x = x;
}

void Explosion::SetPositionY(float y)
{
	m_y = y;
}

void Explosion::SetFrameSize(int w, int h)
{
	assert(m_pAnimatedSprite);
	m_pAnimatedSprite->SetFrameWidth(w);
	m_pAnimatedSprite->SetFrameHeight(h);
}

void Explosion::SetAnimationSpeed(float s)
{
	assert(m_pAnimatedSprite);
	m_pAnimatedSprite->SetFrameSpeed(s);
}



float Explosion::GetPositionX() const
{
	return m_x;
}

float Explosion::GetPositionY() const
{
	return m_y;
}
