#pragma once
#include <list>

class GameStateManager;
class GameObject;

class GameState
{
public:
	enum StateList
	{
		NONE,
		SPLASH,
		MENU,
		LEVEL
	};

	GameState(GameStateManager* manager);

	virtual void Update(float deltaTime) abstract;
	virtual void Draw() abstract;

	GameStateManager* GetGameStateManager() const;

protected:
	GameStateManager* manager;
	std::list<GameObject*>* gameObjects;
};

