#pragma once
#include <map>
#include "Behaviour.h"

class KeyboardBehaviour;
class WanderBehaviour;
class SeekBehaviour;
class MovableGameObject;

class BehaviourMap
{
public:
	BehaviourMap(MovableGameObject* gameObject);

	virtual void Update(float deltaTime) abstract;
	MovableGameObject* GetGameObject() const;
	Behaviour* GetBehaviour(Behaviour::BehaviourList behaviour) const;
	void SetBehaviour(Behaviour::BehaviourList behaviour);

	std::map<Behaviour::BehaviourList, Behaviour*> behaviours;

protected:
	MovableGameObject* gameObject;
	Behaviour* currentBehaviour;
	Behaviour::BehaviourList nextBehaviour;
};

