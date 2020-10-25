#include "NPCBehaviourMap.h"
#include "PathFindBehaviour.h"
#include "AttackBehaviour.h"
#include "MovableGameObject.h"
#include "GameState.h"
#include "LevelState.h"
#include "GameStateManager.h"
#include "Graph.h"

NPCBehaviourMap::NPCBehaviourMap(MovableGameObject* movableGameObject) : BehaviourMap(movableGameObject)
{
	GraphObject* graphObject = ((LevelState*)gameObject->GetGameState())->GetGraphObject();

	currentBehaviour = behaviours[Behaviour::PATHFIND];

	behaviours[Behaviour::PATHFIND] = new PathFindBehaviour(this, graphObject);
	behaviours[Behaviour::ATTACK] = new AttackBehaviour(this);
}

NPCBehaviourMap::~NPCBehaviourMap()
{

}

void NPCBehaviourMap::Update(float deltaTime)
{
	currentBehaviour->Update(deltaTime);
}