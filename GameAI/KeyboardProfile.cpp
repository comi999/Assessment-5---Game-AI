#include "KeyboardProfile.h"

KeyboardProfile::KeyboardProfile()
{

}

KeyboardProfile::~KeyboardProfile()
{

}

void KeyboardProfile::SetKeys(int leftKey, int rightKey, int upKey, int downKey, int mouseButton)
{
	this->leftKey = leftKey;
	this->rightKey = rightKey;
	this->upKey = upKey;
	this->downKey = downKey;
	this->mouseButton = mouseButton;
}