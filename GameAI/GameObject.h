#pragma once

class PopulatedGameState;

class GameObject
{
public:
	GameObject(PopulatedGameState* gameState);

	virtual void Update(float deltaTime) abstract;
	virtual void Draw() abstract;
	PopulatedGameState* GetGameState() const;

protected:
	PopulatedGameState* gameState;
};

