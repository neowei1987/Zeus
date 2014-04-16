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

#endif//ZUES_MEMORY_POOL_H

