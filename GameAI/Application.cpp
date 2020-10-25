#include <time.h>
#include "../Raylib/include/raylib.h"
#include "Application.h"
#include "GameStateManager.h"

Application::Application(const std::string& title, int screenWidth, int screenHeight)
{
	srand(time(NULL));
	InitWindow(screenWidth, screenHeight, title.c_str());

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	gameStateManager = new GameStateManager(this);
}
Application::~Application()
{
	delete gameStateManager;
}

void Application::Run()
{
	while (!WindowShouldClose())
	{
		Update(GetFrameTime());
		Draw();
	}
}

void Application::Shutdown()
{
	CloseWindow();
}

void Application::Update(float deltaTime)
{
	gameStateManager->Update(deltaTime);
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	gameStateManager->Draw();

	EndDrawing();
}

int Application::GetScreenWidth()
{
	return screenWidth;
}

int Application::GetScreenHeight()
{
	return screenHeight;
}