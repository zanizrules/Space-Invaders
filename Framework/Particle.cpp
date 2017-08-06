#include "Particle.h"

Particle::Particle()
{
	Entity::Entity();
}

Particle::~Particle()
{
	Entity::~Entity();
}

void Particle::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}

bool Particle::Initialise(BackBuffer * backbuffer, float x, float y)
{
	return true;
}

