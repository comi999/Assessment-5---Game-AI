#include "PopulatedGameState.h"

PopulatedGameState::PopulatedGameState(GameStateManager* manager) : GameState(manager)
{
	objects = new std::vector<GameObject*>();
}

PopulatedGameState::~PopulatedGameState()
{
	ClearObjects();
	delete objects;
}

void PopulatedGameState::AddObject(GameObject* gameObject)
{
	if (gameObject != nullptr)
		objects->push_back(gameObject);
}

void PopulatedGameState::ClearObjects()
{
	for (GameObject* object : *objects)
		delete object;

	objects->clear();
}