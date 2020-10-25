#pragma once
#include "PopulatedGameState.h"
#include "../Raylib/include/raylib.h"
#include "Player.h"
#include "Enemy.h"
#include "BrainNode.h"

class GameStateManager;
class MovableGameObject;
class GraphObject;

class LevelState : public PopulatedGameState
{
public:
	LevelState(GameStateManager* manager);
	~LevelState();

	void Update(float deltaTime) override;
	void Draw() override;

	void SpawnEnemy();
	Graph<BrainNode>* GetGraph() const;
	GraphObject* GetGraphObject() const;

protected:
	float timer;

	GraphObject* graph;
	Player* player;
	Enemy* corona[5];

	Texture2D* background;
};

