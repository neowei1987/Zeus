
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
#include "queue"
using namespace std; 

/*****************栈的应用**********************/

template <typename T>
class StackWithMax {
public:
    StackWithMax() {
        _max_items.push(INT_MIN);
    }

    void push(T item) {
        _max_items.push(std::max(_max_items.top(), item));
        _items.push(item);
    }

    T pop() {
        if (_item.empty()) {
            throw new exception;
        }

        T r = _items.top();
        _items.pop();
        _max_items.pop();
        return r;
    }

    T max() 
    {
        return _max_items.top();
    }
private:
    stack<T> _items;
    stack<T> _max_items;
};

template <typename T>
class QueueWithMax {
public:
    void push(T item) {
        _in_items.push(item);
    }

    T pop() {
        if (_out_items.empty() && _in_items.empty()) {
            throw new exception;
        }

        if (_out_items.empty()) {
            while (!_in_items.empty()) {
                _out_items.push(_in_items.top());
                _in_items.pop();
            }
        }

        return _out_items.pop();
    }

    T max() 
    {
        return std::max(_in_items.max(), _out_items.max());
    }

private:
    StackWithMax<T> _in_items;
    StackWithMax<T> _out_items;
};


class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }
    
    /** Push element x onto stack. */
    void push(int x) {
        _items.push(x);
    
        int n = _items.size();
        //将之前插入的元素，搞出来，再重新放进去
        while ((n--) > 1) {
            int x = _items.front();
            _items.push(x);
            _items.pop();
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        _items.pop();
    }
    
    /** Get the top element. */
    int top() {
        return _items.front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return _items.empty();
    }

private:
    std::queue<int> _items;
};

class Solution {
public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (k == 1) {
            return nums;
        }

        int n = nums.size();
        vector<int> r;
        deque<int> q;//双端队列
        
        //前k个
        for (int i = 0; i < k - 1; i++) {
            while (!q.empty() && nums[i] > nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(i); //这里有一个点：如果前K个数字为1，3，2，6，8，7；那么容器中的内容为8，7（为什么要这样子，因为窗口需要往前移动）
        }

        for (int i = k - 1; i < n; ++i) {
            if (!q.empty() && q.front() <= i - k) { //移除容器中在窗口之外的元素
                q.pop_front();
            }

            while (!q.empty() && nums[i] > nums[q.back()]) {
                q.pop_back();
            }

            r.push_back(q.empty() ? nums[i] : nums[q.front()]);
            q.push_back(i);
        }

        return r;
    }
};

/*
实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须原地修改，只允许使用额外常数空间。

以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
1,2,3 → 1,3,2
1,3,2 递归问题...
1，3，2； =》 2，1，3 怎么来的？
2，3，1； //tihuanzhhou 
    3,2由于是递减的；所以无法。
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/

int main() 
{ 
    std::stringstream ss;
    ss << "[1,2,3,4]";  
    std::vector<int> pushed;
    std::vector<int> popped;
    int k = 0;
    //std::cin >> nums;
    //std::cin >> k;
    ss >> pushed;

    ss.str("");
    ss << "[7,5,6,4]";
    ss >> popped;

    Solution problem;
    //problem.printNumbers(5);
    //cout << problem.validateStackSequences(pushed, popped);
    //cout << problem.search(nums, k);
    //problem.permute(pushed);
    //cout << problem.majorityElement(popped);
    //problem.getLeastNumbers(popped, 0);
    problem.reversePairs(popped);
    cout << "result: " << popped << "\n";

	return 0; 
} 
