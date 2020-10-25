#pragma once
#include "MovableGameObject.h"

class PopulatedGameState;

class Enemy : public MovableGameObject
{
public:
	Enemy(PopulatedGameState* gameState);
	~Enemy();

	void Draw();
};

