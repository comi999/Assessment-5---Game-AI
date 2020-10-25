#pragma once
#include "GraphObject.h"
#include "Math.h"

struct BrainNode
{
	int id;
	bool occupied;
	GraphObject::NodeKey nodeType;
	Vec2 position;
};