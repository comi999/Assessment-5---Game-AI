#include "GraphObject.h"
#include "../Raylib/include/raylib.h"
#include "GameObject.h"
#include "PopulatedGameState.h"
#include "GameStateManager.h"
#include "BrainNode.h"

GraphObject::GraphObject(PopulatedGameState* gameState) : GameObject(gameState)
{
	graph = new Graph<BrainNode>();
	graveYard = new std::vector<int>();

	Node<BrainNode>* nodes[10];

	nodes[0] = new Node<BrainNode>();

	for (int i = 1; i < 10; i++)
	{
		nodes[i] = new Node<BrainNode>();

		float x = rand() % GetGameState()->GetGameStateManager()->GetAppScreenWidth();
		float y = rand() % GetGameState()->GetGameStateManager()->GetAppScreenHeight();

		nodes[i]->value.position = { x, y };
		graph->InsertEdge(*(nodes[i]), nodes[i - 1], 1);
	}

	for (int i = 0; i < 10; i++)
	{
		graph->InsertNode(nodes[i]);
	}
}

GraphObject::~GraphObject()
{
	delete graph;
}

void GraphObject::Update(float deltaTime)
{
	if (IsKeyPressed(KEY_F)) 
		drawGraph = !drawGraph;
}

void GraphObject::Draw()
{
	if (drawGraph)
	{
		for (int i = 0; i < graph->GetGraph().size(); i++)
		{
			Vec2 pos = graph->GetGraph()[i]->value.position;
			DrawCircle(pos.i, pos.j, 50, BLACK);
		}
	}
}

Graph<BrainNode>* GraphObject::GetGraph() const
{
	return graph;
}

std::vector<int>* GraphObject::GetGraveYard() const
{
	return graveYard;
}

BrainNode* GraphObject::GetNeuron(int index)
{
	return neurons[index];
}