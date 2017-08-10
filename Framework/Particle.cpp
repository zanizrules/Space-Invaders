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
	AgeParticle(deltaTime);
	Entity::Process(deltaTime);
}

bool Particle::Initialise(BackBuffer * backbuffer, float x, float y)
{
	return true;
}

void Particle::AddVelocity(float x, float y)
{
	m_velocityX += x;
	m_velocityY += y;
}

void Particle::AgeParticle(float amount)
{
	m_age += amount;
}

void Particle::AddAcelleration(float x, float y)
{
	m_acelleration.Add(x, y);
}

void Particle::StopAccelerating()
{
}

float Particle::GetMaxAge()
{
	return 0.0f;
}

Vector2D Particle::Acelleration()
{
	return m_acelleration;
}

