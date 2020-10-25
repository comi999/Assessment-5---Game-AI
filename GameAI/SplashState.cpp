#include "SplashState.h"
#include "GameStateManager.h"

SplashState::SplashState(GameStateManager* manager) : GameState(manager)
{
	timer = 0;
	logoAlpha = 0.0f;
	Image logoImage = LoadImage("");
	Texture2D logoTexture = LoadTextureFromImage(logoImage);
	logo = new Texture2D(logoTexture);
}

SplashState::~SplashState()
{

}

void SplashState::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer < 2.0f)
		logoAlpha = timer * 0.5f;
	else if (timer < 4.0f)
		logoAlpha = 1.0f;
	else if (timer < 6.0f)
		logoAlpha = 3.0f - timer * 0.5f;
	else
	{
		manager->SetToSet(MENU);
		manager->SetToRemove(SPLASH);
	}
}

void SplashState::Draw()
{
	Rectangle sourceRec;
	sourceRec.width = logo->width;
	sourceRec.height = logo->height;
	sourceRec.x = 0;
	sourceRec.y = 0;
	Rectangle destRec;
	destRec.width = manager->GetAppScreenWidth();
	destRec.height = manager->GetAppScreenHeight();
	destRec.x = 0;
	destRec.y = 0;

	ClearBackground(Color{ 255, 220, 220 });
	DrawTexturePro(*logo, sourceRec, destRec, { 0, 0 }, 0, Color{ 255, 255, 255, (unsigned char)(logoAlpha * 255) });
}