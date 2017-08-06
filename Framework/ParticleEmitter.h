#pragma once

#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

#include <list>

// Forward Declarations:
class Particle;
class BackBuffer;
class Particle;

class ParticleEmitter
{
	//Member Methods:
public:
	ParticleEmitter();
	~ParticleEmitter();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void SpawnParticle(BackBuffer * backbuffer, float x, float y);
	std::list<Particle*> GetParticles();

protected:

private:
	ParticleEmitter(const ParticleEmitter& entity);

public:

private:
	std::list<Particle*> m_particles;

};

#endif //__PARTICLE_EMITTER_H__