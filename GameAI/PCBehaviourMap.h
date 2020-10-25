#pragma once
#include <map>
#include "BehaviourMap.h"

class Behaviour;
class KeyboardBehaviour;
class KeyboardProfile;
class WanderBehaviour;
class SeekBehaviour;
class GameObject;

class PCBehaviourMap : public BehaviourMap
{
public:
	PCBehaviourMap(MovableGameObject* gameObject, KeyboardProfile* keyboardProfile);
	~PCBehaviourMap();

	void Update(float deltaTime);
};

