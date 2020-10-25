#pragma once
#include "BehaviourMap.h"

class GameObject;

class NPCBehaviourMap : public BehaviourMap
{
public:
	NPCBehaviourMap(MovableGameObject* movableGameObject);
	~NPCBehaviourMap();

	void Update(float deltaTime) override;
};

