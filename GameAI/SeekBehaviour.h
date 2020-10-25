#pragma once
#include "Behaviour.h"
#include "Math.h"

class GameObject;
class BehaviourMap;

class SeekBehaviour : public Behaviour
{
public:
	SeekBehaviour(BehaviourMap* behaviourMap, float maxSeekSpeed);
	~SeekBehaviour();

	bool Update(float deltaTime) override;
	void SetSeekPosition(Vec2 position);

protected:
	float maxSeekSpeed;
	Vec2 seekPosition;
};

