#include "Enemy.h"
#include "NPCBehaviourMap.h"

Enemy::Enemy(PopulatedGameState* gameState) : MovableGameObject(gameState)
{
	behaviourMap = new NPCBehaviourMap(this);
}
Enemy::~Enemy()
{

}

void Enemy::Draw()
{

}