#pragma once

#ifndef ___ENEMY_SHIP_H___
#define ___ENEMY_SHIP_H___

#include "entity.h"

class EnemyShip : public Entity
{
public:
	EnemyShip();
	~EnemyShip();

	void Process(float deltaTime);

private:


};

#endif // ___ENEMY_SHIP_H___
