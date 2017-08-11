#include "Particle.h"

Particle::Particle()
: m_age(0),
m_acelleration()
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

float Particle::GetAge()
{
	return m_age;
}

Vector2D Particle::Acelleration()
{
	return m_acelleration;
}

