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

	if (GetAge() > m_maxage)
	{
		SetDead(true);
	}

	// particleVelocity += particleAcceleration * dt
	m_velocityY += 1; // 9.81f * deltaTime;


	// particlePosition += particleVelocity * dt
	m_y += m_velocityY * deltaTime;

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
