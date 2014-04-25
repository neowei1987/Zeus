#ifndef ZUES_STRUCTURES_LIST_H
#define ZUES_STRUCTURES_LIST_H

//单向链表
struct SingleList
{
	SingleList* next;
};

//双向链表
struct DoubleList
{
	DoubleList* pre;
	DoubleList* next;
};

//初始化
inline void DoubleListInit(DoubleList* list)
{
	list->next = list->pre = list;	
}

//后面插入
inline void DoubleListInsertAfter(DoubleList* list, DoubleList* node)
{
	node->next = list->next;
	node->pre = list;

	list->next->pre = node;
	list->next = node;
}

//前面插入
inline void DoubleListInsertBefore(DoubleList* list, DoubleList* node)
{
	DoubleListInsertAfter(list->pre, node);	
}

//节点删除
inline void DoubleListRemove(DoubleList* node)
{
	node->pre->next = node->next;
	node->next->pre = node->pre;
}

//顺序遍历
#define for_each_entry_at_list(entry, list) \
for (DoubleList* entry = list->next; entry != list; entry = entry->next )

//逆序遍历
#define for_each_entry_at_rev_list(entry, list) \
for (DoubleList* entry = list->pre; entry != list; entry = entry->pre)

#endif//ZUES_STRUCTURES_LIST_H
