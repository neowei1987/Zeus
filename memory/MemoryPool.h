#ifndef ZUES_MEMORY_POOL_H
#define ZUES_MEMORY_POOL_H

#include <sys/types.h>
#include "structures/List.h"

/*
 * 内存池
 * */

struct MemPool
{
	DoubleList* free_head[10];
	DoubleList* free_tail[10];
};

struct MemNode
{
	int size; //大小
	DoubleList free;
	char data[];
};

class MemoryPool
{
public:
	MemoryPool();
	virtual ~MemoryPool();

	//分配内存
	void* alloc(size_t size);
	//释放内存
	void release(void* ptr);
};

//基于二叉树的伙伴内存分配
class BinaryTreeBuddyMemoryPool : MemPool
{
public:
	//假设最底层一共N个叶子节点，则一共需要2*N-1个单位的辅助内存来表示二叉树
	//一块大小为T的内存，最小分配单元为X，则最底层一共有T / X 个子节点
	BinaryTreeBuddyMemoryPool(int minUnitNum, int minUnitSize);

	void* alloc(size_t size);
	void release(void* ptr);
private:
	int parent(int index);
	int lchild(int index);
	int rchild(int index);
private:
	int m_iMinUnitNum; //最小分配单元数量 [2的幂次方]
	int m_iMinUnitSize; //最小分配单元大小
	int m_iMaxSize;
	int* m_pLeftSize;
	char* m_pData;
};

#endif//ZUES_MEMORY_POOL_H

