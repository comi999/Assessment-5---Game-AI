#pragma once

template <typename T>
struct Node;

template <typename T>
struct PFNode
{
public:
	Node<T>* node;
	PFNode<T>* parent;

	int gScore;
	int hScore;
};