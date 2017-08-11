#include "AlienExplosionParticle.h"

#include "Particle.h"
#include "entity.h"
#include "backbuffer.h"
#include "logmanager.h"

#include <string>

AlienExplosionParticle::AlienExplosionParticle()
{
	Particle::Particle();
	AddAcelleration(m_startAcceleration, m_startAcceleration);
}

AlienExplosionParticle::~AlienExplosionParticle()
{
	Particle::~Particle();
}

void AlienExplosionParticle::Process(float deltaTime)
{

	if (GetAge() > m_maxage)
	{
		SetDead(true);
	}

	// particleVelocity += particleAcceleration * dt
	m_velocityX += m_velocityX * Acelleration().m_x * deltaTime;
	m_velocityY += m_velocityY * Acelleration().m_y * deltaTime;

	// particlePosition += particleVelocity * dt
	m_x += m_velocityX * deltaTime;
	m_y += m_velocityY * deltaTime;

	Particle::Process(deltaTime);
}

bool AlienExplosionParticle::Initialise(BackBuffer* m_pBackBuffer, float x, float y)
{
	Sprite* mParticleSprite = m_pBackBuffer->CreateSprite("assets\\alienfragment.png");

	Entity::Initialise(mParticleSprite);

	m_x = x;
	m_y = y;

	return true;
}
