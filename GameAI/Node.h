#pragma once
#include <vector>
#include "Edge.h"

template <typename T>
struct Node
{
	T value;
	std::vector<Edge<T>> connections;
};