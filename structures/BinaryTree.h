#ifndef ZUES_STRUCTURES_BINARY_TREE_H
#define ZUES_STRUCTURES_BINARY_TREE_H

#include <vector>

using std::vector;

/*
 * 二叉树
 * */

//template <typename T> 
//typedef int (*TRAVEL_CALLBACK) (const T& tData); 模版函数暂不支持typedef 

template <typename T>
class BinaryTreeNode
{
public:
	T m_tData;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;

	BinaryTreeNode();
	BinaryTreeNode(const T& tData, BinaryTreeNode* pLeft, BinaryTreeNode* pRight);
	virtual ~BinaryTreeNode();
};

template <typename T>
class BinaryTree
{
public:
	typedef int (*TRAVEL_CALLBACK)(const T&);
public:
	BinaryTree();
	virtual ~BinaryTree();

	//中序遍历串，前序遍历串来进行初始化
	//注意：中序遍历+前序（后序）都可以正确初始化，但是后续，前序无法
	//另外，如果有相同节点，可能会对应多个树，此函数仅返回一个。
	int InitWithTwoSeqs(T* arrInData, T* arrPreData, int iCount);

	//直接插入数据
	BinaryTreeNode<T>* InsertRoot(const T& tData);
	BinaryTreeNode<T>* InsertAsLeftChild(BinaryTreeNode<T>* pParent,const T& tData);
	BinaryTreeNode<T>* InsertAsRightChild(BinaryTreeNode<T>* pParent, const T& tData);

	// 直接插入节点
	int InsertAsLeftChild(BinaryTreeNode<T>* pParent, BinaryTreeNode<T>* pChildNode);
	int InsertAsRightChild(BinaryTreeNode<T>* pParent, BinaryTreeNode<T>* pChildNode);

	//查找
	BinaryTreeNode<T>* Find(const T& tData);
	//查找拥有相同孩子节点的父节点
	int FindSameChild(vector< BinaryTreeNode<T>* >& vctResult);

	//后序遍历
	void PostTravel(TRAVEL_CALLBACK fnCallback);
private:
	BinaryTreeNode<T>* TreeFromSeqs(T* arrInData, int iBegin, int iEnd, T* arrPreData, int iBegin2, int iEnd2);
	int PostTravel(BinaryTreeNode<T>* pNode);
	//注意：前序、后序遍历串，区分不出仅有一个子节点的情况，改正为中序遍历串
	//int GetPreSequence(BinaryTreeNode<T>* pNode, vector< BinaryTreeNode<T>* >& vctResult, vector<T>& vctPreSequence);
	int GetInSequence(BinaryTreeNode<T>* pNode, vector< BinaryTreeNode<T>* >& vctResult, vector<T>& vctInSequence);
private:
	BinaryTreeNode<T>* m_pRoot;
	TRAVEL_CALLBACK m_fnCallback;
};

#include "BinaryTree.hpp"

#endif//ZUES_STRUCTURES_BINARY_TREE_H

