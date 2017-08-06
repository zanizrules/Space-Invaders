#pragma once

#ifndef ___PLAYER_SHIP_H___
#define ___PLAYER_SHIP_H___

#include "entity.h"

class PlayerShip : public Entity
{
public:
	PlayerShip();
	~PlayerShip();

	void Process(float deltaTime);
	bool Initialise(Sprite* sprite);

private:


};

#endif // ___PLAYER_SHIP_H___
