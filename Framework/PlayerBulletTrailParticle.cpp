#include "PlayerBulletTrailParticle.h"

#include "backbuffer.h"

// todo: add in custom processing of particles for different effects

PlayerBulletTrailParticle::PlayerBulletTrailParticle()
{
	//Particle::Particle();
}

PlayerBulletTrailParticle::~PlayerBulletTrailParticle()
{
	Particle::~Particle();
}

bool PlayerBulletTrailParticle::Initialise(BackBuffer* m_pBackBuffer, float x, float y)
{
	Sprite* mParticleSprite = m_pBackBuffer->CreateSprite("assets\\playerbullettrail.png");

	Entity::Initialise(mParticleSprite);

	m_x = x;
	m_y = y;

	return true;
}
