#include "MemoryTestEntry.h"
#include "MemoryPool.h"
#include <stdio.h>
#include <stdlib.h>

int MemoryTestEntry(int argc, char* argv[])
{
	int maxMem = 8 * 1024 * 1024;
	int minSize = 8;
	int count = maxMem / minSize;
	BinaryTreeBuddyMemoryPool pool(count, minSize);

	count = 1000;
	for (int i = 0; i < count; i++)
	{
		void* ptr = pool.alloc(rand() % 1024);
		fprintf(stderr, "%p\n", ptr);
		pool.release((char*)ptr);
	}
	return 0;
}
