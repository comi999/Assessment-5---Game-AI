#include "SeekBehaviour.h"
#include "BehaviourMap.h"
#include "MovableGameObject.h"

SeekBehaviour::SeekBehaviour(BehaviourMap* behaviourMap, float maxSeekSpeed) : Behaviour(behaviourMap)
{
	this->maxSeekSpeed = maxSeekSpeed;
	SetSeekPosition({ 0, 0 });
}

SeekBehaviour::~SeekBehaviour()
{

}

bool SeekBehaviour::Update(float deltaTime)
{
	Vec2 posToTarget = seekPosition - behaviourMap->GetGameObject()->GetPosition();
	Vec2 steeringForce = (posToTarget - behaviourMap->GetGameObject()->GetVelocity()).Normalise() * maxSeekSpeed;
	behaviourMap->GetGameObject()->ApplyForce(steeringForce, deltaTime);
	behaviourMap->GetGameObject()->Move(deltaTime, true);

	if (posToTarget * posToTarget < 100)
		return true;
	else
		return false;
}

void SeekBehaviour::SetSeekPosition(Vec2 seekPosition)
{
	this->seekPosition = seekPosition;
}
