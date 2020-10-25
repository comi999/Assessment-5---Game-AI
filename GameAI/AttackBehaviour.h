#pragma once
#include "Behaviour.h"

class BehaviourMap;

class AttackBehaviour : public Behaviour
{
public:
	AttackBehaviour(BehaviourMap* behaviourMap);
	~AttackBehaviour();

	bool Update(float deltaTime) override;

protected:
	float timer;
};

