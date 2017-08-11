#include "ParticleEmitter.h"
#include "Particle.h"
#include "game.h"

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

	// Remove any dead particles from the container...
	std::list<Particle*>::iterator particleIter = m_particles.begin();
	while (particleIter != m_particles.end())
	{

		// Kill particle if outside of the screen
		(*particleIter)->SetDead(
			(*particleIter)->GetPositionX() <= 0
			|| (*particleIter)->GetPositionX() >= Game::SCREEN_WIDTH - 8
			|| (*particleIter)->GetPositionY() <= 0
			|| (*particleIter)->GetPositionY() >= Game::SCREEN_HEIGHT - 8
			//	|| (*particleIter)->GetHorizontalVelocity() == 0
			//	|| (*particleIter)->GetVerticalVelocity() == 0);
		);

		if ((*particleIter)->IsDead())
		{
			delete *particleIter;
			particleIter = m_particles.erase(particleIter);
		}
		else
		{
			++particleIter;
		}
	}
}

void ParticleEmitter::Draw(BackBuffer& backBuffer)
{
	for (Particle* p : m_particles)
	{
		p->Draw(backBuffer);
	}
}

void ParticleEmitter::SpawnParticle(Particle* pParticle)
{
	m_particles.push_back(pParticle);
}

std::list<Particle*> ParticleEmitter::GetParticles()
{
	return m_particles;
}
