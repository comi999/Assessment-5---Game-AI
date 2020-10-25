#pragma once
#include <functional>
#include <vector>
#include "Behaviour.h"
#include "BrainNode.h"
#include "PathFinder.h"
#include "GraphObject.h"

class BehaviourMap;

class PathFindBehaviour : public Behaviour
{
public:
	PathFindBehaviour(BehaviourMap* behaviourMap, GraphObject* graphObject);
	~PathFindBehaviour();

	bool Update(float deltaTime) override;

	void SetSearchCondition(std::function<bool(Node<BrainNode>*)>* searchCondition);
	void SetSearchHeuristic(std::function<int (Node<BrainNode>*)>* searchHeuristic);

	Node<BrainNode>* GetCurrentNode() const;
	
protected:
	GraphObject* graphObject;
	
	Node<BrainNode>* currentNode;
	GraphObject::NodeKey destinationType;

	PathFinder<BrainNode>* pathFinder;
	std::vector<Node<BrainNode>*>* path;

	std::function<bool(Node<BrainNode>*)>* searchCondition;
	std::function<int (Node<BrainNode>*)>* searchHeuristic;
};

