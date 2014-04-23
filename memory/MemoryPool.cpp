#include "MemoryPool.h"
#include "base/ZuesDefines.h"
#include <stdio.h>

void* MemoryPool::alloc(size_t size)
{
	//找到何时的索引数组
	//找到两条链表，一条用于分配，一条用于回收
	//分配的时候，直接从分配链表中pop一个节点出来，然后挂在
	//回收的时候，
	return NULL;
}

void MemoryPool::release(void* ptr)
{
	// 根据ptr定位到内存节点
	// 然后将该节点挂到分配链表的
}

BinaryTreeBuddyMemoryPool::BinaryTreeBuddyMemoryPool(int minUnitNum, int minUnitSize)
{
	m_iMinUnitNum = UP_TO_POW_2(minUnitNum);
	m_iMinUnitSize = minUnitSize;
	m_iMaxSize = m_iMinUnitSize * m_iMinUnitNum;

	fprintf(stderr, "%d, %d, %d, %d, %d, %d\n", LOG2(minUnitNum), LOG2(m_iMinUnitNum), minUnitNum, m_iMinUnitNum, m_iMinUnitSize, m_iMaxSize);

	// 分配内存
	//假设最底层一共N个叶子节点，则一共需要2*N-1个单位的辅助内存来表示二叉树
	m_pLeftSize = new int[2 * m_iMinUnitNum - 1];
	m_pData = new char[m_iMaxSize] ;

	//建立索引
	int iNodeSize = m_iMaxSize;
	int index = 0;
	while (iNodeSize >= m_iMinUnitSize)
	{
		int count = m_iMaxSize / iNodeSize;
		for (int i = 0; i < count; ++i)
		{
			//fprintf(stderr, "%d => %d\n", index, iNodeSize);
			m_pLeftSize[index++] = iNodeSize;
		}

		iNodeSize /= 2;
	}
	fprintf(stderr, "index ok\n");
}

void* BinaryTreeBuddyMemoryPool::alloc(size_t size)
{
	if (size == 0 )
	{
		return NULL;
	}

	int p = 0;
	int lc = 0;
	int rc = 0;
	int* left = m_pLeftSize;
	bool left_ok = false;
	bool right_ok = false;

	
	//取整为最小分配单元的幂次方
	int round = (size + m_iMinUnitSize - 1) / m_iMinUnitSize; 
	size = m_iMinUnitSize * UP_TO_POW_2(round);
	//printf("alloc %d\n", size);

	if (left[p] < size) //内存不足
	{
		return NULL;
	}

	while (size <= left[p])
	{
		if (p >= m_iMinUnitNum - 1) //当前P表示叶子节点
		{
			left_ok = false;
			right_ok = false;
		}
		else
		{
			lc = lchild(p);		//左节点索引
			rc = rchild(p);		//右节点索引
			//左节点是否能满足
			left_ok = left[lc] >= size;
			//右节点是否能满足
			right_ok = left[rc] >= size;
		}

		//如果当前节点能够满足 && 子节点不能满足时
		if (left[p] == size && !left_ok && !right_ok)
		{
			break;
		}

		if (left[p] >= size) //可以从子节点分配
		{
			if (left_ok && right_ok) //两边都满足条件，优先分配较小节点
			{
				//p = (left[lc] <= left[rc] ? (printf("BL:%d\n", lc),lc) : (printf("BR:%d\n", rc),rc));
				p = (left[lc] <= left[rc] ? (lc) : (rc));
			}
			else if (left_ok) //左边满足
			{
				//printf("L:%d\n", lc);
				p = lc;
			}
			else  //右边满足
			{
				//printf("R:%d\n", rc);
				p = rc;
			}
		}
	}

	int offset = (p + 1) * size - m_iMaxSize;
	printf("size: %d, offset: %d, index: %d\n", size, offset, p);

	//调整节点以及父节点容量
	int n = 0;
	int m = p;
	left[m]	= 0; 
	while (m > 0)
	{
		p = parent(m); //父节点
		n = (lchild(p) == m ? m + 1 : m - 1); //兄弟节点
		if (left[m] <= left[n] && left[n] == left[p])//如果减了大小的节点，依旧小于另一个节点，并且父节点，已经取了兄弟节点的值，则结束
		{
			break;
		}
		else //否则，调整父节点容量
		{
			left[p] = (left[m] > left[n] ? left[m] : left[n]);
		//	printf("%d, %d, %d, %d\n", p, left[p], left[m], left[n]);
			m = p;
		}
	}

	return (m_pData + offset);
}

void BinaryTreeBuddyMemoryPool::release(void* ptr)
{
	int offset = (long)ptr - (long)m_pData;
	//判断是否合法内存
	if (offset < 0 || (offset > (m_iMaxSize - m_iMinUnitSize)) || (offset % m_iMinUnitSize))
	{
		printf("this ptr is not allocated by this pool\n");
		return;
	}
	//转化为叶子节点的偏移
	int index = offset / m_iMinUnitSize + m_iMinUnitNum - 1;
	//向上迭代，直到找到容量为0的节点，表示已经定位到了当时分配内存的索引节点[包括大小]
	int p = index;
	int iNodeSize = m_iMinUnitSize;
	while (p > 0)
	{
		if (m_pLeftSize[p] == 0)
		{
			break;
		}

		iNodeSize *= 2;
		p = parent(p);
	}

	printf("release %d, %d\n", p, m_pLeftSize[p]);
	if (p > 0 || (p == 0 && m_pLeftSize[p] == 0)) //合法内存
	{
		int m = p;
		int n = 0;
		m_pLeftSize[m] = iNodeSize;
		//向上回溯，如果可以的话合并
		while (m > 0)
		{
			iNodeSize *= 2;
			p = parent(m);	//父节点，可能发生变化，如果不发生变化，则循环退出
			n = (lchild(p) == m ? m + 1 : m - 1); //兄弟节点，未发生变化
			if (m_pLeftSize[m] + m_pLeftSize[n] == iNodeSize)
			{
				m_pLeftSize[p] = iNodeSize; //父节点发生变化
				m = p;
			}
			else
			{
				if (m_pLeftSize[m] <= m_pLeftSize[n]) //父节点大小保持不变，退出
				{
					break;
				}
				else
				{
					m_pLeftSize[p] = m_pLeftSize[m]; // 父节点发生变化
					m = p;
				}
			}
		}
	}
	else
	{
		printf("ptr not found\n");
	}
}

int BinaryTreeBuddyMemoryPool::parent(int index)
{
	return (index - 1) >> 1;
}

int BinaryTreeBuddyMemoryPool::lchild(int index)
{
	return (index << 1) + 1;
}

int BinaryTreeBuddyMemoryPool::rchild(int index)
{
	return (index << 1) + 2;
}
