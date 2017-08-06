#include "AlienExplosionParticle.h"

#include "Particle.h"
#include "backbuffer.h"

// todo: add in custom processing of particles for different effects

AlienExplosionParticle::AlienExplosionParticle()
{

}

AlienExplosionParticle::~AlienExplosionParticle()
{

}

bool AlienExplosionParticle::Initialise(BackBuffer* m_pBackBuffer, float x, float y)
{
	Sprite* mParticleSprite = m_pBackBuffer->CreateSprite("assets\\alienfragment.png");

	Entity::Initialise(mParticleSprite);

	m_x = x;
	m_y = y;

	return true;
}
