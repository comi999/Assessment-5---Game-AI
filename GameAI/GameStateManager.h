#pragma once
#include <map>
#include "GameState.h"

class Application;
class GameState;

class GameStateManager final
{
public:
	GameStateManager(Application* application);
	~GameStateManager();

	void Update(float deltaTime);
	void Draw();

	GameState* GetCurrentState() const;

	void SetToSet(GameState::StateList state);
	void SetToRemove(GameState::StateList state);

	Application* GetApplication() const;
	int GetAppScreenWidth() const;
	int GetAppScreenHeight() const;

protected:
	Application* application;
	std::map<GameState::StateList, GameState*>* states;

	GameState* currentState;

	GameState::StateList toSet;
	GameState::StateList toRemove;
};

