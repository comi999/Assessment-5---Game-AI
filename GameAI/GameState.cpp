#include "GameState.h"

GameState::GameState(GameStateManager* manager)
{
	this->manager = manager;
	this->gameObjects = new std::list<GameObject*>();
}

GameStateManager* GameState::GetGameStateManager() const
{
	return manager;
}