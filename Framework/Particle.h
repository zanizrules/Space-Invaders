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

private:
	Vector2D m_velocity;
	Vector2D m_acelleration;
	// current age
	// maximum age


};

#endif // ___PARTICLE_H___