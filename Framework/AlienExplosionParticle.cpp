#include "AlienExplosionParticle.h"

#include "Particle.h"
#include "entity.h"
#include "backbuffer.h"

AlienExplosionParticle::AlienExplosionParticle()
{
	Particle::Particle();
}

AlienExplosionParticle::~AlienExplosionParticle()
{
	Particle::~Particle();
}

void AlienExplosionParticle::Process(float deltaTime)
{
	
	// todo: add in custom processing of particles for different effects
	// Updates each particle: motion, age, other effects…
	// Acceleration changes velocity over time (delta velocity)
	// Velocity changes position over time(delta position)
	// particleVelocity += particleAcceleration * dt
	// And : particlePosition += particleVelocity * dt

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
