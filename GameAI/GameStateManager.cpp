#include "GameStateManager.h"
#include "Application.h"
#include "SplashState.h"
#include "MenuState.h"
#include "LevelState.h"

GameStateManager::GameStateManager(Application* application)
{
	this->application = application;

	states = new std::map<GameState::StateList, GameState*>();

	(*states)[GameState::SPLASH] = new SplashState(this);
	(*states)[GameState::MENU]   = new MenuState(this);
	(*states)[GameState::LEVEL]  = new LevelState(this);

	currentState = nullptr;

	toSet    = GameState::SPLASH;
	toRemove = GameState::NONE;
}

GameStateManager::~GameStateManager()
{
	for (auto& entry : *states)
		delete entry.second;

	delete states;
}

void GameStateManager::Update(float deltaTime)
{
	if (toSet != GameState::NONE)
	{
		auto state = states->find(toSet);

		if (state != states->end())
			currentState = state->second;

		toSet = GameState::NONE;
	}

	if (toRemove != GameState::NONE)
	{
		auto state = states->find(toRemove);

		if (state != states->end())
		{
			delete state->second;
			states->erase(state);
		}

		toRemove = GameState::NONE;
	}

	currentState->Update(deltaTime);
}

void GameStateManager::Draw()
{
	currentState->Draw();
}

GameState* GameStateManager::GetCurrentState() const
{
	return currentState;
}

void GameStateManager::SetToSet(GameState::StateList state)
{
	toSet = state;
}

void GameStateManager::SetToRemove(GameState::StateList state)
{
	toRemove = state;
}

Application* GameStateManager::GetApplication() const
{
	return application;
}

int GameStateManager::GetAppScreenWidth() const
{
	return application->GetScreenWidth();
}

int GameStateManager::GetAppScreenHeight() const
{
	return application->GetScreenHeight();
}