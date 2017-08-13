#include "SmallStarParticle.h"

#include "Particle.h"
#include "entity.h"
#include "backbuffer.h"

#include <string>

SmallStarParticle::SmallStarParticle()
{
	Particle::Particle();
}

SmallStarParticle::~SmallStarParticle()
{
	Particle::~Particle();
}

void SmallStarParticle::Process(float deltaTime)
{
	// particlePosition += particleVelocity * dt
	m_x += m_velocityX * deltaTime;
	m_y += m_velocityY * deltaTime;

	Particle::Process(deltaTime);
}

bool SmallStarParticle::Initialise(BackBuffer* m_pBackBuffer, float x, float y)
{
	Sprite* mParticleSprite = m_pBackBuffer->CreateSprite("assets\\smallstar.png");

	Entity::Initialise(mParticleSprite);

	m_x = x;
	m_y = y;

	return true;
}
