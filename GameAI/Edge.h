#pragma once

template <typename T>
struct Node;

template <typename T>
struct Edge
{
public:
	Node<T>* toNode;
	int weight;
};