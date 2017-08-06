#include "ParticleEmitter.h"
#include "Particle.h"

ParticleEmitter::ParticleEmitter()
{

}

ParticleEmitter::~ParticleEmitter()
{
	for (Particle* p : m_particles)
	{
		delete p;
	}
}

void ParticleEmitter::Process(float deltaTime)
{
	for (Particle* p : m_particles)
	{
		p->Process(deltaTime);
	}
}

void ParticleEmitter::Draw(BackBuffer& backBuffer)
{
	for (Particle* p : m_particles)
	{
		p->Draw(backBuffer);
	}
}

void ParticleEmitter::SpawnParticle(BackBuffer* backbuffer, float x, float y)
{
	Particle* pParticle = new Particle();
	pParticle->Initialise(backbuffer, x, y);

	m_particles.push_back(pParticle);
}

std::list<Particle*> ParticleEmitter::GetParticles()
{
	return m_particles;
}
