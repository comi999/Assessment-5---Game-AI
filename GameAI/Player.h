#pragma once
#include <map>
#include <string>
#include "../Raylib/include/raylib.h"
#include "MovableGameObject.h"

class PopulatedGameState;
class KeyboardProfile;

class Player : public MovableGameObject
{
public:
	Player(PopulatedGameState* gameState, KeyboardProfile* keyboardProfile);
	~Player();
	void Draw() override;

protected:
	int leftKey;
	int rightKey;
	int upKey;
	int downKey;
};

