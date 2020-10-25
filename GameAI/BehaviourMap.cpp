#include "BehaviourMap.h"

BehaviourMap::BehaviourMap(MovableGameObject* gameObject)
{
	this->gameObject = gameObject;
	currentBehaviour = nullptr;
	nextBehaviour = Behaviour::NONE;
}

MovableGameObject* BehaviourMap::GetGameObject() const
{
	return gameObject;
}

Behaviour* BehaviourMap::GetBehaviour(Behaviour::BehaviourList behaviour) const
{
	auto result = behaviours.find(behaviour);
	if (result != behaviours.end())
		return result->second;
	else
		return nullptr;
}

void BehaviourMap::SetBehaviour(Behaviour::BehaviourList behaviour)
{
	nextBehaviour = behaviour;
}