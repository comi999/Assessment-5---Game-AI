#include <map>
#include "BehaviourMap.h"
#include "Behaviour.h"
#include "PCBehaviourMap.h"
#include "KeyBoardBehaviour.h"
#include "KeyboardProfile.h"
#include "WanderBehaviour.h"
#include "SeekBehaviour.h"
#include "MovableGameObject.h"
#include "../Raylib/include/raylib.h"

PCBehaviourMap::PCBehaviourMap(MovableGameObject* gameObject, KeyboardProfile* keyboardProfile) :
	BehaviourMap(gameObject)
{
	behaviours[Behaviour::WANDER] = new WanderBehaviour(this, 30, 300);
	behaviours[Behaviour::SEEK] = new SeekBehaviour(this, 300);
	behaviours[Behaviour::KEYBOARD] = new KeyBoardBehaviour(this, &behaviours, keyboardProfile, 500);

	currentBehaviour = behaviours[Behaviour::KEYBOARD];
}

PCBehaviourMap::~PCBehaviourMap()
{

}

void PCBehaviourMap::Update(float deltaTime)
{
	currentBehaviour->Update(deltaTime);
}