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

private:


};

#endif // ___ALIEN_EXPLOSION_PARTICLE_H___
