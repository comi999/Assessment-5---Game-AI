#include "LevelState.h"
#include "GameStateManager.h"
#include "KeyBoardBehaviour.h"
#include "KeyboardProfile.h"
#include "Player.h"
#include "Enemy.h"
#include "GraphObject.h"

LevelState::LevelState(GameStateManager* manager) : PopulatedGameState(manager)
{
	KeyboardProfile* keyboardProfile = new KeyboardProfile();
	keyboardProfile->SetKeys(KEY_A, KEY_D, KEY_W, KEY_S, MOUSE_LEFT_BUTTON);

	timer = 0;
	background = new Texture2D(LoadTextureFromImage(LoadImage("Assets/level.png")));

	player = new Player(this, keyboardProfile);
	graph = new GraphObject(this);
}

LevelState::~LevelState()
{
	delete player;
	delete graph;
}

void LevelState::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer > 10)
	{
		SpawnEnemy();
		timer = 0;
	}

	for (auto& object : *gameObjects)
		object->Update(deltaTime);
}

void LevelState::Draw()
{
	Rectangle sourceRec;
	sourceRec.width = background->width;
	sourceRec.height = background->height;
	sourceRec.x = 0;
	sourceRec.y = 0;
	Rectangle destRec;
	destRec.width = manager->GetAppScreenWidth();
	destRec.height = manager->GetAppScreenHeight();
	destRec.x = 0;
	destRec.y = 0;

	DrawTexturePro(*background, sourceRec, destRec, { 0, 0 }, 0, RAYWHITE);

	for (auto& object : *gameObjects)
		object->Draw();
}

void LevelState::SpawnEnemy()
{
	for (int i = 0; i < 5; i++)
	{
		if (corona[i] == nullptr)
		{
			corona[i] = new Enemy(this);
			return;
		}
	}
}

Graph<BrainNode>* LevelState::GetGraph() const
{
	return graph->GetGraph();
}

GraphObject* LevelState::GetGraphObject() const
{
	return graph;
}