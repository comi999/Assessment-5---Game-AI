#include "Player.h"
#include "PCBehaviourMap.h"
#include "KeyboardProfile.h"
#include "PopulatedGameState.h"
#include "GameStateManager.h"

Player::Player(PopulatedGameState* gameState, KeyboardProfile* keyboardProfile) : MovableGameObject(gameState)
{
	int screenWidth = gameState->GetGameStateManager()->GetAppScreenWidth();
	int screenHeight = gameState->GetGameStateManager()->GetAppScreenHeight();

	SetPosition({ (float)screenWidth - 10, 10 });
	SetVelocity({ 0, 0 });
	SetFriction(0.9f);
	SetMaxVelocity(1000);

	behaviourMap = new PCBehaviourMap(this, keyboardProfile);
}

Player::~Player() 
{

}

void Player::Draw()
{
	DrawCircle(position.i, position.j, 30, RED);
	DrawLine(position.i, position.j, position.i + velocity.i, position.j + velocity.j, BLACK);
}