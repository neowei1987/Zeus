#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class MedianFinder {
private:
    priority_queue<int, vector<int>, greater<int> > _bigger_half;
    priority_queue<int, vector<int>, less<int> > _smaller_half;

public:
    /** initialize your data structure here. */
    MedianFinder() {

    }
    
    void addNum(int num) {
        if (_bigger_half.size() && num > _bigger_half.top()) {
            _bigger_half.push(num);
        }
        else {
            _smaller_half.push(num);
        }

        if (_bigger_half.size() >= _smaller_half.size() + 2) {
            _smaller_half.push(_bigger_half.top());
            _bigger_half.pop();
        }
        else if (_smaller_half.size() >= _bigger_half.size() + 2) {
            _bigger_half.push(_smaller_half.top());
            _smaller_half.pop();
        }
    }

    double findMedian() {
        if ((_bigger_half.size() + _smaller_half.size()) % 2) {
            return _bigger_half.size() > _smaller_half.size() ? _bigger_half.top() : _smaller_half.top();
        }
        else {
            return (1.0 * _bigger_half.top() + _smaller_half.top()) / 2;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */