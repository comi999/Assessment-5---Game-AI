#pragma once
#include <queue>
#include <stack>
#include <map>
#include <functional>
#include "Graph.h"
#include "BinaryTree.h"
#include "PFNode.h"

template <typename T>
class PathFinder
{
public:
	enum SEARCH_ALGORITHM
	{
		BREADTHFIRST,
		DEPTHFIRST,
		DIJKSTRA,
		ASTAR
	};

	PathFinder(Graph<T>* graph);
	~PathFinder();

	void InitSearch(SEARCH_ALGORITHM searchAlgorthm, Node<T>* startNode, int maxIterations);
	void AbandonSearch();

	void SetSearchCondition(std::function<bool(Node<T>*)>* searchCondition);
	void SetSearchHeuristic(std::function<int (Node<T>*)>* searchHeuristic);

	bool UpdateSearch(int iterations = 1);
	bool ExtractPath(std::vector<Node<T>*>& path) const;

protected:
	PFNode<T>* ConstructPFNode(Node<T>* node, PFNode<T>* parent, int gScore = 0, int hScore = 0);

	void PushToOpenedList(PFNode<T>* PFNode);
	void PushToClosedList(PFNode<T>* PFNode);

	PFNode<T>* PullFromOpenedList();
	void DestroyOpenedList();

	Graph<T>* graph;
	SEARCH_ALGORITHM algorithm;
	Node<T>* startNode;
	PFNode<T>* finalNode;
	bool searchInProgress;
	int currentIteration;
	int maxIterations;

	std::function<bool(Node<T>*)>* searchCondition;
	std::function<int (Node<T>*)>* searchHeuristic;

	template <bool useHeuristic>
	class Compare
	{
	public:
		bool operator() (PFNode<T>* lhs, PFNode<T>* rhs) const
		{
			return lhs->gScore + lhs->hScore * useHeuristic > 
				   rhs->gScore + rhs->hScore * useHeuristic;
		}
	};

	union
	{
		std::queue<PFNode<T>*>* qOpenedList;
		std::stack<PFNode<T>*>* sOpenedList;
		std::priority_queue<PFNode<T>*, std::vector<PFNode<T>*>, Compare<0>>* dOpenedList;
		std::priority_queue<PFNode<T>*, std::vector<PFNode<T>*>, Compare<1>>* aOpenedList;
	} openedList;

	BinaryTree<Node<T>*> openedTree;
	BinaryTree<Node<T>*> closedTree;

	std::map<Node<T>*, PFNode<T>> openMap;
};

template <typename T>
PathFinder<T>::PathFinder(Graph<T>* graph)
{
	this->graph = graph;
	startNode = nullptr;
	finalNode = nullptr;
	searchInProgress = false;
	currentIteration = 0;
	maxIterations = 0;
}

template <typename T>
PathFinder<T>::~PathFinder()
{
	delete searchCondition;
	delete searchHeuristic;
	DestroyOpenedList();
}

template <typename T>
void PathFinder<T>::InitSearch(SEARCH_ALGORITHM searchAlgorithm, Node<T>* startNode, int maxIterations)
{
	if (searchAlgorithm == BREADTHFIRST)
		openedList.qOpenedList = new std::queue<PFNode<T>*>();
	else if (searchAlgorithm == DEPTHFIRST)
		openedList.sOpenedList = new std::stack<PFNode<T>*>();
	else if (searchAlgorithm == DIJKSTRA)
		openedList.dOpenedList = new std::priority_queue<PFNode<T>*, std::vector<PFNode<T>*>, Compare<0>>();
	else if (searchAlgorithm == ASTAR)
		openedList.aOpenedList = new std::priority_queue<PFNode<T>*, std::vector<PFNode<T>*>, Compare<1>>();

	algorithm = searchAlgorithm;
	this->startNode = startNode;
	searchInProgress = true;
	currentIteration = 0;
	this->maxIterations = maxIterations;

	PFNode<T>* startPFNode = ConstructPFNode(startNode, nullptr);
	PushToOpenedList(startPFNode);
}

template <typename T>
void PathFinder<T>::AbandonSearch()
{
	startNode = nullptr;
	finalNode = nullptr;
	searchInProgress = false;
	currentIteration = 0;
	maxIterations = 0;

	DestroyOpenedList();

	openedTree.Clear();
	closedTree.Clear();
}

template <typename T>
void PathFinder<T>::SetSearchCondition(std::function<bool(Node<T>*)>* searchCondition)
{
	this->searchCondition = searchCondition;
}

template <typename T>
void PathFinder<T>::SetSearchHeuristic(std::function<int(Node<T>*)>* searchHeuristic)
{
	this->searchHeuristic = searchHeuristic;
}

template <typename T>
bool PathFinder<T>::UpdateSearch(int iterations)
{
	if (!searchInProgress)
		return false;

	PFNode<T>* current;

	int limit = (iterations > 0) ? iterations : 1;
	bool underMaxIterations = true;

	for (int i = 0; i < limit && underMaxIterations; i += (iterations > 0))
	{
		current = PullFromOpenedList();

		if ((*searchCondition)(current->node))
		{
			searchInProgress = false;
			finalNode = current;
			return true;
		}

		for (const Edge<T>& edge : current->node->connections)
		{
			bool inLists = openedTree.Contains(edge.toNode);

			if (algorithm == BREADTHFIRST || algorithm == DEPTHFIRST)
				inLists = inLists || closedTree.Contains(edge.toNode);

			if (inLists && (algorithm == DIJKSTRA || algorithm == ASTAR))
			{
				PFNode<T>& pfnode = openMap[edge.toNode];

				if (pfnode.gScore > current->gScore + edge.weight)
				{
					pfnode.gScore = current->gScore + edge.weight;
					pfnode.parent = current;
				}
			}

			if (!inLists)
			{
				PFNode<T>& pfnode = openMap[edge.toNode];

				pfnode.node = edge.toNode;
				pfnode.parent = current;
				pfnode.gScore = current->gScore + edge.weight;
				pfnode.hScore = (algorithm == ASTAR) ? (*searchHeuristic)(edge.toNode) : 0;

				PushToOpenedList(&pfnode);
			}
		}
		
		currentIteration++;

		if (maxIterations > 0)
			underMaxIterations = currentIteration < maxIterations;
	}

	if (currentIteration == maxIterations)
		searchInProgress = false;

	return false;
}

template <typename T>
bool PathFinder<T>::ExtractPath(std::vector<Node<T>*>& path) const
{
	if (finalNode)
	{
		PFNode<T>* current = finalNode;
		path.clear();

		while (current != nullptr)
		{
			path.insert(path.begin(), current->node);
			current = current->parent;
		}

		return true;
	}
	else
		return false;
}

template <typename T>
PFNode<T>* PathFinder<T>::ConstructPFNode(Node<T>* node, PFNode<T>* parent, int gScore, int hScore)
{
	PFNode<T>* newPFNode = new PFNode<T>();
	newPFNode->node = node;
	newPFNode->parent = parent;
	newPFNode->gScore = gScore;
	newPFNode->hScore = hScore;
	return newPFNode;
}

template <typename T>
void PathFinder<T>::PushToOpenedList(PFNode<T>* PFNode)
{
	if (algorithm == BREADTHFIRST)
		openedList.qOpenedList->push(PFNode);
	else if (algorithm == DEPTHFIRST)
		openedList.sOpenedList->push(PFNode);
	else if (algorithm == DIJKSTRA)		
		openedList.dOpenedList->push(PFNode);
	else if (algorithm == ASTAR)
		openedList.aOpenedList->push(PFNode);

	openedTree.Insert(PFNode->node);
}

template <typename T>
void PathFinder<T>::PushToClosedList(PFNode<T>* PFNode)
{
	closedTree.Insert(PFNode->node);
}

template <typename T>
PFNode<T>* PathFinder<T>::PullFromOpenedList()
{
	PFNode<T>* node = nullptr;

	if (algorithm == BREADTHFIRST)
	{
		if (openedList.qOpenedList->empty()) 
			return node;

		node = openedList.qOpenedList->front();
		openedList.qOpenedList->pop();
	}
	else if (algorithm == DEPTHFIRST)
	{
		if (openedList.sOpenedList->empty())
			return node;

		node = openedList.sOpenedList->top();
		openedList.sOpenedList->pop();
	}
	else if (algorithm == DIJKSTRA)
	{
		if (openedList.dOpenedList->empty())
			return node;

		node = openedList.dOpenedList->top();
		openedList.dOpenedList->pop();
	}
	else if (algorithm == ASTAR)
	{
		if (openedList.aOpenedList->empty())
			return node;

		node = openedList.aOpenedList->top();
		openedList.aOpenedList->pop();
	}

	openedTree.Remove(node->node);

	return node;
}

template <typename T>
void PathFinder<T>::DestroyOpenedList()
{
	if (algorithm == BREADTHFIRST)
		delete openedList.qOpenedList;
	else if (algorithm == DEPTHFIRST)
		delete openedList.sOpenedList;
	else if (algorithm == DIJKSTRA)
		delete openedList.dOpenedList;
	else if (algorithm == ASTAR)
		delete openedList.aOpenedList;
}