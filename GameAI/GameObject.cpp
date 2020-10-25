#include "GameObject.h"
#include "PopulatedGameState.h"

GameObject::GameObject(PopulatedGameState* gameState)
{
	this->gameState = gameState;
	gameState->AddObject(this);
}

PopulatedGameState* GameObject::GetGameState() const
{
	return gameState;
}