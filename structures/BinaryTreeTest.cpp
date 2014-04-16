#include <stdio.h>
#include "BinaryTree.h"

int printNode(const int& iNode)
{
	printf("%d", iNode);
	return 0;
}

int BinaryTreeTestEntry(int argc, char* argv[])
{
	BinaryTree<int> myTree;
	//int arrInData[] = {4, 2, 8, 3, 7, 1, 6};
	//int arrPreData[] = {3, 2, 4, 8, 1, 7, 6};
	//int arrInData[] = {3, 7, 1, 6};
	//int arrPreData[] = {3, 1, 7, 6};
	int arrInData[] = {1, 3, 2, 1, 3};
	int arrPreData[] = {2, 3, 1, 3, 1};
	myTree.InitWithTwoSeqs(arrInData, arrPreData, sizeof(arrInData) / sizeof(arrInData[0]));
	myTree.PostTravel(printNode);
	vector< BinaryTreeNode<int>* > vctResult;
	myTree.FindSameChild(vctResult);
	return 0;
}
