#pragma once
#include <list>
#include <string>

class GameStateManager;

class Application
{
public:
	Application(const std::string& title, int screenWidth, int screenHeight);
	~Application();

	void Run();
	void Shutdown();

	void Update(float deltaTime);
	void Draw();
	
	int GetScreenWidth();
	int GetScreenHeight();

protected:
	int screenWidth;
	int screenHeight;

	GameStateManager* gameStateManager;

};

