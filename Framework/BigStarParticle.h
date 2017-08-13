#pragma once

#ifndef ___BIG_STAR_PARTICLE_H___
#define ___BIG_STAR_PARTICLE_H___

#include "Particle.h"

class BigStarParticle : public Particle
{
public:
	BigStarParticle();
	~BigStarParticle();

	bool Initialise(BackBuffer* m_pBackBuffer, float x, float y) override;

	void Process(float deltaTime) override;

private:


};

#endif // ___BIG_STAR_PARTICLE_H___
