#pragma once
#include "GameState.h"

class GameStateManager;

class MenuState : public GameState
{
public:
	MenuState(GameStateManager* manager);
	~MenuState();

	void Update(float deltaTime) override;
	void Draw() override;

protected:
	float timer;
};