#pragma once
#include "Behaviour.h"

class GameObject;
class BehaviourMap;

class WanderBehaviour : public Behaviour
{
public:
	WanderBehaviour(BehaviourMap* behaviourMap, int directionOffset, float wanderSpeed);
	~WanderBehaviour();

	bool Update(float deltaTime) override;

protected:
	int directionOffset;
	float wanderSpeed;
	float directionTimer;
};

