#pragma once
#include "Math.h"
#include "GameObject.h"

class Behaviour;
class BehaviourMap;
class PopulatedGameState;

class MovableGameObject : public GameObject
{
public:
	MovableGameObject(PopulatedGameState* gameState);
	~MovableGameObject();

	virtual void Update(float deltaTime) override;

	//Getters
	const Vec2& GetPosition() const;
	const Vec2& GetVelocity() const;
	const float GetFriction() const;

	const float GetMaxVelocity() const;

	//Setters
	void SetPosition(const Vec2& pos);
	void SetVelocity(const Vec2& vel);
	void SetFriction(float friction);

	void SetMaxVelocity(float vel);

	void ApplyForce(const Vec2& force, float deltaTime);
	void ApplyFriction(float deltaTime);

	void Move(float deltaTime, bool withFriction);

	Vec2 position;
	Vec2 velocity;
	float friction;
	float maxVelocity;

	float timer;

protected:
	BehaviourMap* behaviourMap;
};

