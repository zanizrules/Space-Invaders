#pragma once

#ifndef ___BULLET_H___
#define ___BULLET_H___

#include "entity.h"

class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();

	bool IsCollidingWith(Entity * e);

	void Process(float deltaTime);

private:


};

#endif // ___BULLET_H___
