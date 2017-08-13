#pragma once

#ifndef ___SMALL_STAR_PARTICLE_H___
#define ___SMALL_STAR_PARTICLE_H___

#include "Particle.h"

class SmallStarParticle : public Particle
{
public:
	SmallStarParticle();
	~SmallStarParticle();

	bool Initialise(BackBuffer* m_pBackBuffer, float x, float y) override;

	void Process(float deltaTime) override;

private:


};

#endif // ___SMALL_STAR_PARTICLE_H___
