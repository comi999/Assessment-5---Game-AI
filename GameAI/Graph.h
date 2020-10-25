#pragma once
#include <vector>
#include "Node.h"
#include "Edge.h"

template <typename T>
class Graph
{
public:
	Graph();
	~Graph();

	Node<T>* ConstructNode(const T& value);
	void InsertEdge(Node<T>& node, Node<T>* toNode, int weight, bool createReverseEdge = true);
	void InsertNode(Node<T>* node);

	const std::vector<Node<T>*>& GetGraph();
	void ClearGraph();

protected:
	std::vector<Node<T>*> graph;
};

template <typename T>
Graph<T>::Graph()
{

}

template <typename T>
Graph<T>::~Graph()
{

}

template <typename T>
Node<T>* Graph<T>::ConstructNode(const T& value)
{
	Node<T>* newNode = new Node<T>();
	newNode->value = value;
	return newNode;
}

template <typename T>
void Graph<T>::InsertEdge(Node<T>& node, Node<T>* toNode, int weight, bool createReverseEdge)
{
	node.connections.push_back(Edge<T>{toNode, weight});
	if (createReverseEdge)
		toNode->connections.push_back(Edge<T>{&node, weight});
}

template <typename T>
void Graph<T>::InsertNode(Node<T>* node)
{
	graph.push_back(node);
}

template <typename T>
const std::vector<Node<T>*>& Graph<T>::GetGraph()
{
	return graph;
}

template <typename T>
void Graph<T>::ClearGraph()
{
	graph.clear();
}