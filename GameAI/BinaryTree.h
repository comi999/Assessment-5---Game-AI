#include "TreeNode.h"

template <typename T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	TreeNode<T>* GetRoot() const;
	bool IsEmpty() const;
	void Insert(const T& value);
	void Insert(TreeNode<T>* node);
	void Remove(const T& value);
	TreeNode<T>* Find(const T& value) const;
	bool Contains(const T& value) const;
	void Clear();

private:
	bool FindNode(const T& searchValue, TreeNode<T>*& outNode, TreeNode<T>*& outParent) const;

	TreeNode<T>* root;
};

template <typename T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
	while (root)
		Remove(root->GetData());
}

template <typename T>
TreeNode<T>* BinaryTree<T>::GetRoot() const
{
	return root;
}

template <typename T>
bool BinaryTree<T>::IsEmpty() const
{
	return (root == nullptr);
}

template <typename T>
void BinaryTree<T>::Insert(const T& value)
{
	if (root == nullptr)
	{
		root = new TreeNode<T>(value);
		return;
	}

	TreeNode<T>* selectedNode = root;

	while (selectedNode->GetData() != value)
	{
		if (selectedNode->GetData() > value)
		{
			if (selectedNode->GetLeft() != nullptr)
				selectedNode = selectedNode->GetLeft();
			else
				selectedNode->SetLeft(new TreeNode<T>(value));
		}
		else
		{
			if (selectedNode->GetRight() != nullptr)
				selectedNode = selectedNode->GetRight();
			else
				selectedNode->SetRight(new TreeNode<T>(value));
		}
	}
}

template <typename T>
void BinaryTree<T>::Insert(TreeNode<T>* node)
{
	if (!node)
		return;

	if (root == nullptr)
	{
		root = node;
		return;
	}

	TreeNode<T>* selectedNode = root;
	while (selectedNode->GetData() != node->GetData())
	{
		if (selectedNode->GetData() > node->GetData())
		{
			if (selectedNode->GetLeft() != nullptr)
				selectedNode = selectedNode->GetLeft();
			else
				selectedNode->SetLeft(node);
		}
		else
		{
			if (selectedNode->GetRight() != nullptr)
				selectedNode = selectedNode->GetRight();
			else
				selectedNode->SetRight(node);
		}
	}
}

template <typename T>
TreeNode<T>* BinaryTree<T>::Find(const T& value) const
{
	TreeNode<T>* current = nullptr;
	TreeNode<T>* parent = nullptr;

	return FindNode(value, current, parent) ? current : nullptr;
}

template <typename T>
bool BinaryTree<T>::Contains(const T& value) const
{
	if (!Find(value))
		return false;
	else
		return true;
}

template <typename T>
void BinaryTree<T>::Clear()
{
	delete root;
}

template <typename T>
bool BinaryTree<T>::FindNode(const T& searchValue, TreeNode<T>*& outNode, TreeNode<T>*& outParent) const
{
	if (root == nullptr)
		return false;

	outNode = root;

	while (outNode->GetData() != searchValue)
	{
		outParent = outNode;

		if (outNode->GetData() > searchValue)
		{
			if (outNode->GetLeft() != nullptr)
			    outNode = outNode->GetLeft();
			else
				return false;
		}
		else
		{
			if (outNode->GetRight() != nullptr)
				outNode = outNode->GetRight();
			else
				return false;
		}
	}

	return true;
}

template <typename T>
void BinaryTree<T>::Remove(const T& value)
{
	TreeNode<T>* outNode = nullptr;
	TreeNode<T>* outParent = nullptr;

	if (!FindNode(value, outNode, outParent))
		return;

	TreeNode<T>* leftNode =  outNode->GetLeft();
	TreeNode<T>* rightNode = outNode->GetRight();

	if (outParent)
	{
		if (outParent->GetLeft() == outNode)
			outParent->SetLeft(nullptr);
		else
			outParent->SetRight(nullptr);
	}
	else
		root = nullptr;

	delete outNode;

	if (leftNode)
		Insert(leftNode);
	if (rightNode)
		Insert(rightNode);
}