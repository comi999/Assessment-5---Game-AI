#include "PathFindBehaviour.h"
#include "BehaviourMap.h"
#include "MovableGameObject.h"

PathFindBehaviour::PathFindBehaviour(BehaviourMap* behaviourMap, GraphObject* graphObject) : Behaviour(behaviourMap)
{
	this->graphObject = graphObject;
	pathFinder = new PathFinder<BrainNode>(graphObject->GetGraph());
	path = new std::vector<Node<BrainNode>*>();

	*searchCondition = [&](Node<BrainNode>* node) -> bool
	{
		bool inGraveYard = false;
		std::vector<int>* graveYard = graphObject->GetGraveYard();

		for (int i = 0; i < graveYard->size(); i++)
		{
			if ((*graveYard)[i] == node->value.id)
				inGraveYard = true;
			break;
		}

		if (node->value.nodeType == GraphObject::NEURON && !node->value.occupied && inGraveYard)
		{
			node->value.occupied = true;
			return true;
		}

		return false;
	};

	*searchHeuristic = [&](Node<BrainNode>* node) -> int
	{
		float minDistance = 5000;

		Vec2 currentPos = currentNode->value.position;

		for (int i = 0; i < 5; i++)
		{
			BrainNode* currentNode = graphObject->GetNeuron(i);

			if (currentNode->occupied)
				continue;

			float distance = (currentNode->position - currentPos).Magnitude();
			
			minDistance = (distance < minDistance) ? distance : minDistance;
		}

		return minDistance;
	};

	pathFinder->SetSearchCondition(searchCondition);
	pathFinder->SetSearchHeuristic(searchHeuristic);
}

PathFindBehaviour::~PathFindBehaviour()
{

}

bool PathFindBehaviour::Update(float deltaTime)
{
	if (path->empty() && !pathFinder->UpdateSearch(1))
	{
		pathFinder->AbandonSearch();
		pathFinder->InitSearch(PathFinder<BrainNode>::ASTAR, currentNode, 100);
	}
	else if (path->empty())
		pathFinder->ExtractPath(*path);
	else
	{
		Vec2 posToTarget = path->at(0)->value.position - behaviourMap->GetGameObject()->GetPosition();
		Vec2 steeringForce = (posToTarget - behaviourMap->GetGameObject()->GetVelocity()).Normalise() * 300;
		behaviourMap->GetGameObject()->ApplyForce(steeringForce, deltaTime);
		behaviourMap->GetGameObject()->Move(deltaTime, true);

		if (posToTarget * posToTarget < 100)
		{
			currentNode = path->at(0);
			path->erase(path->begin());
		}

		if (path->empty())
			behaviourMap->SetBehaviour(Behaviour::ATTACK);
	}

	return true;
}

void PathFindBehaviour::SetSearchCondition(std::function<bool(Node<BrainNode>*)>* searchCondition)
{
	pathFinder->SetSearchCondition(searchCondition);
}

void PathFindBehaviour::SetSearchHeuristic(std::function<int(Node<BrainNode>*)>* searchHeuristic)
{
	pathFinder->SetSearchHeuristic(searchHeuristic);
}

Node<BrainNode>* PathFindBehaviour::GetCurrentNode() const
{
	return currentNode;
}