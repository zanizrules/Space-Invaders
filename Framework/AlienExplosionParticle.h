#pragma once

#ifndef ___ALIEN_EXPLOSION_PARTICLE_H___
#define ___ALIEN_EXPLOSION_PARTICLE_H___

#include "Particle.h"

class AlienExplosionParticle : public Particle
{
public:
	AlienExplosionParticle();
	~AlienExplosionParticle();

	bool Initialise(BackBuffer* m_pBackBuffer, float x, float y) override;

	void Process(float deltaTime) override;

	float GetMaxAge();

	const float m_maxage = 0.05f;

private:


};

#endif // ___ALIEN_EXPLOSION_PARTICLE_H___
