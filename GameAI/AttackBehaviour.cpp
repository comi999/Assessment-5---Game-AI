#include "AttackBehaviour.h"
#include "PathFindBehaviour.h"
#include "NPCBehaviourMap.h"
#include "MovableGameObject.h"
#include "LevelState.h"

AttackBehaviour::AttackBehaviour(BehaviourMap* behaviourMap) : Behaviour(behaviourMap)
{
	timer = 0;
}

AttackBehaviour::~AttackBehaviour()
{

}

bool AttackBehaviour::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer > 5)
	{
		int currentId = ((PathFindBehaviour*)(behaviourMap->behaviours[Behaviour::PATHFIND]))->GetCurrentNode()->value.id;
		((LevelState*)behaviourMap->
			GetGameObject()->
			GetGameState())->
			GetGraphObject()->
			GetGraveYard()->
			push_back(currentId);

		behaviourMap->SetBehaviour(Behaviour::PATHFIND);
		timer = 0;
	}

	return true;
}