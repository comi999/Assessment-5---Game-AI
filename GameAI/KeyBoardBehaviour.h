#pragma once
#include "Behaviour.h"
#include "KeyboardProfile.h"

class GameObject;
class BehaviourMap;

class KeyBoardBehaviour : public Behaviour
{
public:

	KeyBoardBehaviour(BehaviourMap* behaviourMap, std::map<Behaviour::BehaviourList, Behaviour*>* behaviours, KeyboardProfile* keyboardProfile, float force);
	~KeyBoardBehaviour();

	bool Update(float deltaTime) override;

protected:
	float timer;
	float force;

	std::map<Behaviour::BehaviourList, Behaviour*>* behaviours;
	Behaviour::BehaviourList currentSubBehaviour;

	KeyboardProfile* keyboardProfile;
	int& leftKey = keyboardProfile->leftKey;
	int& rightKey = keyboardProfile->rightKey;
	int& upKey = keyboardProfile->upKey;
	int& downKey = keyboardProfile->downKey;
	int& mouseButton = keyboardProfile->mouseButton;

	bool leftKeyDown;
	bool rightKeyDown;
	bool upKeyDown;
	bool downKeyDown;
	bool mouseButtonDown;
};

