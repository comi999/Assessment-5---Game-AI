#pragma once
#include "Math.h"
#include "GameObject.h"
#include "Graph.h"

class GameState;
struct BrainNode;

class GraphObject : public GameObject
{
public:
	enum NodeKey
	{
		NONE,
		VIRUS_SOURCE,
		NEURON,
		PLAYER_SOURCE
	};

	GraphObject(PopulatedGameState* gameState);
	~GraphObject();

	void Update(float deltaTime) override;
	void Draw() override;

	Graph<BrainNode>* GetGraph() const;
	std::vector<int>* GetGraveYard() const;
	BrainNode* GetNeuron(int index);

protected:
	Graph<BrainNode>* graph;
	bool drawGraph;

	BrainNode* neurons[5];
	std::vector<int>* graveYard;
};

