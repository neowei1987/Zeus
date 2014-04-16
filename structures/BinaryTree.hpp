#include <stddef.h>

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode()
{
	m_pLeft = NULL;
	m_pRight = NULL;
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& tData, BinaryTreeNode<T>* pLeft, BinaryTreeNode<T>* pRight)
{
	m_tData = tData;
	m_pLeft = pLeft;
	m_pRight = pRight;
}

template <typename T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
	//TODO
}

template <typename T>
BinaryTree<T>::BinaryTree()
{
	m_pRoot = NULL;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
	//TODO
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::InsertRoot(const T& tData)
{
	return NULL;	
}

template <typename T>
int BinaryTree<T>::InitWithTwoSeqs(T* arrInData, T* arrPreData, int iCount)
{
	BinaryTreeNode<T>* pNode = TreeFromSeqs(arrInData, 0, iCount - 1, arrPreData, 0, iCount - 1);
	if (pNode != NULL)
	{
		m_pRoot = pNode;
		return 0;
	}
	else
	{
		fprintf(stderr, "invalid seqs\n");
		return -1;
	}
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::TreeFromSeqs(T* arrInData, int iBegin, int iEnd, T* arrPreData, int iBegin2, int iEnd2)
{
	fprintf(stderr, "%d:%d, %d:%d\n", iBegin, iEnd, iBegin2, iEnd2);
	if (iBegin > iEnd)
	{
		return NULL;
	}

	if (iBegin == iEnd && iBegin2 == iEnd2)
	{
		if (arrInData[iBegin] == arrPreData[iBegin2])
		{
			return new BinaryTreeNode<T>(arrPreData[iBegin2], NULL, NULL);
		}
		else
		{
			return NULL;
		}
	}

	T& tRoot = arrPreData[iBegin2];
	//遍历中序序列
	for (int i = iBegin; i <= iEnd; i++) //
	{
		if (arrInData[i] == tRoot)
		{
			fprintf(stderr, "%d at %d\n", tRoot, i);
			BinaryTreeNode<T>* pLeftNode = NULL;
			BinaryTreeNode<T>* pRightNode = NULL;
			pLeftNode = TreeFromSeqs(arrInData, iBegin, i - 1, arrPreData, iBegin2 + 1, iBegin2 + (i - iBegin));	
			pRightNode = TreeFromSeqs(arrInData, i + 1, iEnd, arrPreData, iEnd2 - (iEnd - i - 1), iEnd2);	
			if (pLeftNode != NULL || pRightNode != NULL)
			{
				return new BinaryTreeNode<T>(tRoot, pLeftNode, pRightNode);
			}
		}
	}

	return NULL;
}

template <typename T>
void BinaryTree<T>::PostTravel(TRAVEL_CALLBACK fnCallback)
{
	if (m_pRoot)
	{
		m_fnCallback = fnCallback;	
		PostTravel(m_pRoot);
	}
}

template <typename T>
int BinaryTree<T>::PostTravel(BinaryTreeNode<T>* pNode)
{
	if (pNode->m_pLeft)
	{
		PostTravel(pNode->m_pLeft);
	}	
	if (pNode->m_pRight)
	{
		PostTravel(pNode->m_pRight);
	}

	m_fnCallback(pNode->m_tData);

	return 0;
}

template <typename T>
int BinaryTree<T>::GetInSequence(BinaryTreeNode<T>* pNode, vector< BinaryTreeNode<T>* >& vctResult, vector<T>& vctSequence)
{
	if (pNode == NULL)
	{
		return 0;
	}

	int iLeftNum = GetInSequence(pNode->m_pLeft, vctResult, vctSequence);
	vctSequence.push_back(pNode->m_tData);
	int iRightNum = GetInSequence(pNode->m_pRight, vctResult, vctSequence);

	if (iLeftNum == iRightNum && iLeftNum > 0 )
	{
		int i = 0;
		int iRightOffset = vctSequence.size() - iLeftNum;
		int iLeftOffset = iRightOffset - iLeftNum - 1;
		while (i < iLeftNum)
		{
			if (vctSequence[iLeftOffset + i] != vctSequence[iRightOffset + i])
			{
				break;
			}
			i++;
		}
		if (i == iLeftNum)
		{
			printf("i got one: %d\n", pNode->m_tData);
			vctResult.push_back(pNode);	
		}
	}

	return iLeftNum + iRightNum + 1;
}

template <typename T>
int BinaryTree<T>::FindSameChild(vector< BinaryTreeNode<T>* >& vctResult)
{
	vector<T> vctInSequence;
	vctResult.clear();
	GetInSequence(m_pRoot, vctResult, vctInSequence);

	printf("in sequence:\n");
	for (int i = 0; i < vctInSequence.size(); ++i)
	{
		printf("%d", vctInSequence[i]);
	}
	printf("\n");
	
	return 0;
}

/*
template <typename T>
int IsSameTree(BinaryTreeNode<T>* pParent, BinaryTreeNode<T>* pNode1, BinaryTreeNode<T>* pNode2)
{
	if (pNode1->m_pLeft == NULL )
	{
	}
	if (pNode1->m_tData == pNode2->m_tData)
	{
		bool bLeftSame = IsSameTree(pNode1->m_pLeft, pNode2->m_pLeft);
		bool bRightSame = IsSameTree(pNode1->m_pRight, pNode2->m_pRight);
		if (bLeftSame && bRightSame)
		{
			//write down the parent as one result.
			return true;
		}
	}
	else
	{
		return false;
	}
}
*/
