#include <map>
#include "KeyBoardBehaviour.h"
#include "BehaviourMap.h"
#include "SeekBehaviour.h"
#include "MovableGameObject.h"
#include "../Raylib/include/raylib.h"

KeyBoardBehaviour::KeyBoardBehaviour(BehaviourMap* behaviourMap, std::map<Behaviour::BehaviourList, Behaviour*>* behaviours, KeyboardProfile* keyboardProfile, float force) :
	Behaviour(behaviourMap)
{
	this->behaviours = behaviours;

	this->keyboardProfile = keyboardProfile;

	bool leftKeyDown = false;
	bool rightKeyDown = false;
	bool upKeyDown = false;
	bool downKeyDown = false;
	bool mouseButtonDown = false;
	
	this->force = force;
	timer = 0;
}

KeyBoardBehaviour::~KeyBoardBehaviour()
{

}

bool KeyBoardBehaviour::Update(float deltaTime)
{
	timer += deltaTime;

	leftKeyDown = IsKeyDown(keyboardProfile->leftKey);
	rightKeyDown = IsKeyDown(keyboardProfile->rightKey);
	upKeyDown = IsKeyDown(keyboardProfile->upKey);
	downKeyDown = IsKeyDown(keyboardProfile->downKey);
	mouseButtonDown = IsMouseButtonPressed(keyboardProfile->mouseButton);

	if (leftKeyDown || rightKeyDown || upKeyDown || downKeyDown)
	{
		timer = 0;

		if (leftKeyDown)  behaviourMap->GetGameObject()->ApplyForce({ -force, 0 }, deltaTime);
		if (rightKeyDown) behaviourMap->GetGameObject()->ApplyForce({  force, 0 }, deltaTime);
		if (upKeyDown)    behaviourMap->GetGameObject()->ApplyForce({ 0, -force }, deltaTime);
		if (downKeyDown)  behaviourMap->GetGameObject()->ApplyForce({ 0,  force }, deltaTime);

		behaviourMap->GetGameObject()->Move(deltaTime, true);

		currentSubBehaviour = NONE;
	}
	else if (mouseButtonDown)
	{
		timer = 0;
		currentSubBehaviour = SEEK;

		Vector2 mousePos = GetMousePosition();
		((SeekBehaviour*)behaviourMap->behaviours[SEEK])->SetSeekPosition({ mousePos.x, mousePos.y });
	}
	else if (currentSubBehaviour == SEEK)
	{
		if (behaviourMap->behaviours[currentSubBehaviour]->Update(deltaTime)) 
			currentSubBehaviour = WANDER;
	}
	else if (timer > 2)
	{
		currentSubBehaviour = WANDER;
		behaviourMap->behaviours[currentSubBehaviour]->Update(deltaTime);
	}
	else if (currentSubBehaviour == NONE)
	{
		behaviourMap->GetGameObject()->Move(deltaTime, true);
	}

	leftKeyDown = false;
	rightKeyDown = false;
	upKeyDown = false;
	downKeyDown = false;
	mouseButtonDown = false;

	return true;
}