#include "PlayerBulletTrailParticle.h"

#include "backbuffer.h"

PlayerBulletTrailParticle::PlayerBulletTrailParticle()
{
	Particle::Particle();
}

PlayerBulletTrailParticle::~PlayerBulletTrailParticle()
{
	Particle::~Particle();
}

void PlayerBulletTrailParticle::Process(float deltaTime)
{

	// todo: add in custom processing of particles for different effects
	// Updates each particle: motion, age, other effects…

	// particleAccerlation -= gravity

	Particle::Process(deltaTime);
}

bool PlayerBulletTrailParticle::Initialise(BackBuffer* m_pBackBuffer, float x, float y)
{
	Sprite* mParticleSprite = m_pBackBuffer->CreateSprite("assets\\playerbullettrail.png");

	Entity::Initialise(mParticleSprite);

	m_x = x;
	m_y = y;

	return true;
}
