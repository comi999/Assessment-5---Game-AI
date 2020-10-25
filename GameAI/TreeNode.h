#pragma once
#include "../Raylib/include/raylib.h"
#include <string>

template <typename T>
class TreeNode
{
public:
	TreeNode(T value);
	~TreeNode();

	bool HasLeft() { return (left != nullptr); }
	bool HasRight() { return (right != nullptr); }

	T GetData() { return value; }
	TreeNode<T>* GetLeft() { return left; }
	TreeNode<T>* GetRight() { return right; }

	void SetData(T value) { value = value; }
	void SetLeft(TreeNode<T>* node) { left = node; }
	void SetRight(TreeNode<T>* node) { right = node; }
	
private:
	T value;

	TreeNode<T>* left;
	TreeNode<T>* right;
};

template <typename T>
TreeNode<T>::TreeNode(T value)
{
	this->value = value;
	left = nullptr;
	right = nullptr;
}

template <typename T>
TreeNode<T>::~TreeNode()
{
	//delete left;
	//delete right;
}