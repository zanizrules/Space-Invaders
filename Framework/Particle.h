#pragma once

#ifndef ___PARTICLE_H___
#define ___PARTICLE_H___

#include "entity.h"
#include "Vector2D.h"

class Particle : public Entity
{
public:
	Particle();
	~Particle();

	virtual void Process(float deltaTime);
	virtual bool Initialise(BackBuffer* backbuffer, float x, float y);

	void AddVelocity(float x, float y);
	void AgeParticle(float amount);
	void AddAcelleration(float x, float y);
	void StopAccelerating();
	virtual float GetMaxAge();

	Vector2D Acelleration();


private:
	Vector2D m_acelleration;
	float m_age;
};

#endif // ___PARTICLE_H___