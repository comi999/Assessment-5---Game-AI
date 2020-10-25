#pragma once
#include "GameState.h"
#include <raylib.h>

class GameStateManager;

class SplashState : public GameState
{
public:
	SplashState(GameStateManager* manager);
	~SplashState();

	void Update(float deltaTime) override;
	void Draw() override;

protected:
	float timer;
	float logoAlpha;
	Texture2D* logo;
};