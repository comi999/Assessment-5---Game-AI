#include "Math.h"
#include "MovableGameObject.h"
#include "BehaviourMap.h"
#include "WanderBehaviour.h"
#include "PopulatedGameState.h"
#include "GameStateManager.h"

WanderBehaviour::WanderBehaviour(BehaviourMap* behaviourMap, int directionOffset, float wanderSpeed) : Behaviour(behaviourMap)
{
	this->directionOffset = directionOffset;
	this->wanderSpeed = wanderSpeed;
	directionTimer = 0;
}

WanderBehaviour::~WanderBehaviour()
{

}

bool WanderBehaviour::Update(float deltaTime)
{
	directionTimer += deltaTime;
	
	if (directionTimer > 0.1f)
	{
		int screenWidth = behaviourMap->GetGameObject()->GetGameState()->GetGameStateManager()->GetAppScreenWidth();
		int screenHeight = behaviourMap->GetGameObject()->GetGameState()->GetGameStateManager()->GetAppScreenHeight();

		Vec2 position = behaviourMap->GetGameObject()->GetPosition();
		if (position.i < 10 || position.i > screenWidth - 10 ||
			position.j < 10 || position.j > screenHeight - 10)
		{
			Vec2 centreDirection = Vec2{ screenWidth  * 0.5f, 
				                         screenHeight * 0.5f } -
				                         behaviourMap->GetGameObject()->GetPosition();
			centreDirection = centreDirection.Normalise() * wanderSpeed;
			behaviourMap->GetGameObject()->SetVelocity(centreDirection);
		}
		else
		{
			Vec2 velocity = behaviourMap->GetGameObject()->GetVelocity();
			float theta = atan2f(velocity.i, -velocity.j) * 57.296f;
	
			theta = theta - directionOffset + rand() % (2 * directionOffset);
			theta *= 0.017f;
	
			velocity.i = wanderSpeed * sinf(theta);
			velocity.j = -wanderSpeed * cosf(theta);
	
			behaviourMap->GetGameObject()->SetVelocity(velocity);
			directionTimer = 0;
		}
	}
	
	behaviourMap->GetGameObject()->Move(deltaTime, false);
	
	return true;
};