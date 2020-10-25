#pragma once
#include <vector>
#include "GameState.h"

class GameObject;

class PopulatedGameState : public GameState
{
public:
	PopulatedGameState(GameStateManager* manager);
	~PopulatedGameState();

	void AddObject(GameObject* gameObject);
	void ClearObjects();

protected:
	std::vector<GameObject*>* objects;
};

