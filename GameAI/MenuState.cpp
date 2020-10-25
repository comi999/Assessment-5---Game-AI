#include "MenuState.h"
#include "../Raylib/include/raylib.h"
#include "GameStateManager.h"

MenuState::MenuState(GameStateManager* manager) : GameState(manager)
{
	timer = 0.0f;
}

MenuState::~MenuState()
{

}

void MenuState::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer > 3.0f)
	{
		GetGameStateManager()->SetToSet(LEVEL);
		GetGameStateManager()->SetToRemove(MENU);
	}
}

void MenuState::Draw()
{
	ClearBackground(GREEN);
}