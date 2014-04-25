#include "List.h"
#include "base/ZuesDefines.h"

struct Item
{
public:
	int m_i;
	DoubleList list;

	Item(int i)
	{
		m_i = i;
	}
};

int ListTestEntry(int argc, char*argv[])
{
	Item* t1 = new Item(1);
	Item* t2 = new Item(2);
	Item* t3 = new Item(3);
	Item* t4 = new Item(4);
	Item* t5 = new Item(5);

	DoubleList* itemListHead = new DoubleList();
	DoubleListInit(itemListHead);
	DoubleListInsertAfter(itemListHead, &(t1->list));
	DoubleListInsertAfter(&(t1->list), &(t2->list));
	DoubleListInsertBefore(&(t2->list), &(t3->list));
	DoubleListInsertAfter(&(t3->list), &(t4->list));
	DoubleListInsertAfter(&(t4->list), &(t5->list));
	DoubleListRemove(&(t3->list));
	//for_each_entry_at_list(entry, itemListHead)
	for_each_entry_at_rev_list(entry, itemListHead)
	{
		Item* ptr = CONTAINER_PTR(entry, Item, list);
	//	printf("item t1: %p\n", t1);
		printf("%d", ptr->m_i);
	}
	printf("\n");
	return 0;
}
