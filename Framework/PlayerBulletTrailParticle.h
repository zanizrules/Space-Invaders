#pragma once

#ifndef ___PLAYER_BULLET_TRAIL_PARTICLE_H___
#define ___PLAYER_BULLET_TRAIL_PARTICLE_H___

#include "Particle.h"

class PlayerBulletTrailParticle : public Particle
{
public:
	PlayerBulletTrailParticle();
	~PlayerBulletTrailParticle();

	bool Initialise(BackBuffer* m_pBackBuffer, float x, float y) override;

private:


};

#endif // ___PLAYER_BULLET_TRAIL_PARTICLE_H___
