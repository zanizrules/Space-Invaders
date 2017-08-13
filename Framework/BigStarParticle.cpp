#include "BigStarParticle.h"

#include "Particle.h"
#include "entity.h"
#include "backbuffer.h"

BigStarParticle::BigStarParticle()
{
	Particle::Particle();
}

BigStarParticle::~BigStarParticle()
{
	Particle::~Particle();
}

bool BigStarParticle::Initialise(BackBuffer* m_pBackBuffer, float x, float y)
{
	Sprite* mParticleSprite = m_pBackBuffer->CreateSprite("assets\\biggerstar.png");

	Entity::Initialise(mParticleSprite);

	m_x = x;
	m_y = y;

	return true;
}

void BigStarParticle::Process(float deltaTime)
{
	// particlePosition += particleVelocity * dt
	m_x += m_velocityX * deltaTime;
	m_y += m_velocityY * deltaTime;

	Particle::Process(deltaTime);
}
