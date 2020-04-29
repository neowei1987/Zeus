
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
#incude "queue"
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

    /*队列最大值
    实现思路：
    1. 利用两个stack，实现一个stack with max
    2. 利用两个stack, 实现一个queue;
    3. max = max(max(stack1), max(stack2));
    */
    int QueueWithMaxImpl() {
        return 0;
    };

    int trap(vector<int>& height) {
        stack<int> s;
        int res = 0;
        for (int i = 0; i < height.size(); ++i) {
            while (s.size() & height[i] > height[s.top()]) {
                auto t = height[s.top()];
                s.pop();
                if (s.empty()) break;
                res += (min(height[s.top()], height[i]) - t) * (i - s.top() - 1);
            } 
            s.push(i);
        }
        return res;
    }

    int surfaceArea(vector<vector<int>>& grid) {
        int area = 0; 
        if (grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }
        int h = grid.size();
        int w = grid[0].size();
        for (int i = 0 ; i < h; ++i) {
            int pre = 0;
            for (int j = 0; j < w; ++j) {
                area += (!!grid[i][j] << 1); //Z轴
                area += (grid[i][j]  > pre ? ((grid[i][j] - pre) << 1) : 0);
                pre = grid[i][j] ;
            }  
        }

        for (int j = 0 ; j < w; ++j) {
            int pre = 0;
            for (int i = 0; i < h; ++i) {
                area += (grid[i][j]  > pre ? ((grid[i][j] - pre) << 1) : 0);
                pre = grid[i][j] ;
            }
        }

        return area;
    }

    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if (pushed.size() != popped.size()) {
            return false;
        }
        if (pushed.empty()) {
            return true;
        }
        int n =  pushed.size();
        stack<int> s;
        int i = 0;  //指向pop序列
        int k = 0;  //指向pushed序列
        s.push(-1);
        while (i < n) {
            cout << "compared:"  << popped[i] << " vs " << s.top() << endl;
            if (s.top() != popped[i]) {
                bool matched = false;
                for (; k < n; ++k) {
                    if (pushed[k] != popped[i]) {
                        cout << "pushed:"  << pushed[k] << endl;
                        s.push(pushed[k]);
                    }
                    else {
                        matched = true;
                        i++;
                        k++;
                        break;
                    }
                }
                if (!matched) {
                    if (k == n) {
                        return false;
                    }
                }
            }
            else {
                cout << "popped:"  << s.top() << endl;
                s.pop();
                
                i++;
            }
        }
        return true;
    }
};

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
