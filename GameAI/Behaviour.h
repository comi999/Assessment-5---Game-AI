#pragma once

class GameObject;
class BehaviourMap;
class PCBehaviourMap;

class Behaviour
{
public:
	enum BehaviourList
	{
		NONE,
		KEYBOARD,
		WANDER,
		SEEK,
		PATHFIND,
		ATTACK
	};

	Behaviour(BehaviourMap* behaviourMap);

	virtual bool Update(float deltaTime) abstract;

protected:
	BehaviourMap* behaviourMap;
};

