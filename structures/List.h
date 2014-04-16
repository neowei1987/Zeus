#ifndef ZUES_STRUCTURES_LIST_H
#define ZUES_STRUCTURES_LIST_H

//单向链表
struct SingleList
{
	SingleList* next;
};

struct SingleListHead
{
};

struct Item
{
	struct SingleList itemList;
};

//双向链表
struct DoubleList
{
	DoubleList* pre;
	DoubleList* next;
};

#define SINGLE_LiST_INSERT() 


#endif//ZUES_STRUCTURES_LIST_H
