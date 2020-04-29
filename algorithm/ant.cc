
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

class ListNode  {
public:
    ListNode(int value) {
        _value = value;
    }

private:
    int _value;
    ListNode* next;
    ListNode* pre;
}

class LRUCache {
public:
    LRUCache(size_t size) : _max_size(size) {

    }

    int add(int key, int value){

        if (_item.size() >= size) {
            _recent_accessed.pop_back();
            //释放内存
            delete xx;
        }

        auto it = _items.find(key);
        ListNode* newNode = NULL;
        if (it == _items.end()) { //已经存在，
            return -1;
        }
        else {
            newNode = new ListNode(value);
            _items.insert(key, newNode);
        }

        //将新的item，添加到链表头部
        _recent_accessed.push_front(newNode);
        return 0;
    }   


    int get(int key) {
        auto it = _items.find();
        if (it == _items.end()) {
            return -1;
        }

        //根据it能够在尽可能短的时间内找到
        //找到对应的元素，放到链表头部？
        _recent_accessed.erase(it->second);
        _recent_accessed.front(it->second);

        return it->second->val;
    }

private:
    size_t _max_size;
    std::map<int, ListNode*> _items; 
    std::linked_list<ListNode*> _recent_accessed;

};

int main() 
{ 
	return 0; 
} 
