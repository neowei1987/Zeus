#include <stdio.h>
#include "Heap.h"

int HeapTestEntry(int argc, char* argv[])
{
	//MinHeap<int> heap;
	//MinHeap<int> heap;
	//TopKContainer<int, Heap<int> > heap(2);
	TopKContainer<int, MinHeap<int> > heap(2);
	heap.push(5);
	heap.push(6);
	heap.push(1);
	heap.push(3);
	heap.push(11);
	heap.push(12);
	heap.push(9);
	heap.push(10);
	while (!heap.empty())
	{
		printf("%d\n", heap.top());
		heap.pop();
	}
	return 0;
}
