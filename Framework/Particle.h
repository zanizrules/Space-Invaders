#pragma once

#ifndef ___PARTICLE_H___
#define ___PARTICLE_H___

#include "entity.h"

class Particle : public Entity
{
public:
	Particle();
	~Particle();

	void Process(float deltaTime);
	virtual bool Initialise(BackBuffer* backbuffer, float x, float y);

private:


};

#endif // ___PARTICLE_H___