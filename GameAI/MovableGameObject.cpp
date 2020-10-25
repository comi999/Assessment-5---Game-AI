#include "Application.h"
#include "MovableGameObject.h"
#include "BehaviourMap.h"

MovableGameObject::MovableGameObject(PopulatedGameState* gameState) : GameObject(gameState)
{
	
}

MovableGameObject::~MovableGameObject()
{

}

void MovableGameObject::Update(float deltaTime)
{
	behaviourMap->Update(deltaTime);
}

const Vec2& MovableGameObject::GetPosition() const
{
	return position;
}

const Vec2& MovableGameObject::GetVelocity() const
{
	return velocity;
}

const float MovableGameObject::GetFriction() const
{
	return friction;
}

const float MovableGameObject::GetMaxVelocity() const
{
	return maxVelocity;
}

void MovableGameObject::SetPosition(const Vec2& pos)
{
	position = pos;
}

void MovableGameObject::SetVelocity(const Vec2& vel)
{
	velocity = vel;
}

void MovableGameObject::SetFriction(float fri)
{
	friction = fri;
}

void MovableGameObject::SetMaxVelocity(float vel)
{
	maxVelocity = vel;
}

void MovableGameObject::ApplyForce(const Vec2& force, float deltaTime)
{
	velocity += force * deltaTime;

	velocity.i = (velocity.i >  maxVelocity) ?  maxVelocity : velocity.i;
	velocity.i = (velocity.i < -maxVelocity) ? -maxVelocity : velocity.i;
	velocity.j = (velocity.j >  maxVelocity) ?  maxVelocity : velocity.j;
	velocity.j = (velocity.j < -maxVelocity) ? -maxVelocity : velocity.j;
}

void MovableGameObject::ApplyFriction(float deltaTime)
{
	ApplyForce(velocity * -friction, deltaTime);
}

void MovableGameObject::Move(float deltaTime, bool withFriction)
{
	if (withFriction)
		ApplyFriction(deltaTime);

	position += velocity * deltaTime;
}