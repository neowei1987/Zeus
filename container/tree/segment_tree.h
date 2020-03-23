#include <vector>

/*
根源：分块思想的树化
分块思想的本质：通过将整个序列分为有穷个小块，对于要查询的一段区间，总是可以整合成k个所分块与m个单个元素的信息的并(0≤k,m≤sqrt{n})
相比线段树只能维护符合结合律的信息，
例如min, max, sum, xor；而分块可以维护很多别的东西。
具体可以维持的操作包括但不限于：
求最大值，求最小值，最大公约数， 
RMQ， RSQ

https://www.cnblogs.com/AC-King/p/7789013.html

*/
inline int left_son(int p) {return p << 1;}
inline int right_son(int p) {return p << 1 | 1;}

typedef int (*NORMAL_OPERATION_FUNC)(const std::vector<int>&, int, int);
class SegmentTree
{
public:
    void push_up(int p) {
         _tree_result[p] = _normal_func(_tree_source, _tree_result[left_son(p)], _tree_result[right_son(p)]);
    }

    void build(int p, int left, int right) {
        if (left == right) {
            _tree_result[p] = left;
            return;
        }

        int mid = left + ((right - left) >> 1);
        build(left_son(p), left, mid); //左子树
        build(right_son(p), mid + 1, right); //右子树

        push_up(p);  
    };

    SegmentTree(const std::vector<int>& nums, NORMAL_OPERATION_FUNC func) 
        : _tree_source(nums), _normal_func(func) {
        if (nums.empty()) {
            return;
        }

        _tree_result.resize(4 * nums.size());
        build(1, 0 , nums.size() - 1);
    }

    void update() {

    }

    //0，0，0，1
    int _rangeQuery(int start, int end, int p, int left, int right) {
        if (start <= left && end >= right) { //[start, end]完全覆盖了[left, right]
            return _tree_result[p];
        }
        
        int mid = left + ((right - left) >> 1);
        int result = -1;
        if (start <= mid) {
            result = _rangeQuery(start, end, left_son(p), left, mid);
        }
        
        if (end > mid)
        {
            if (result < 0) {
                 result = _rangeQuery(start, end, right_son(p), mid + 1, right);
            }
            else {
                result = _normal_func(_tree_source, result, _rangeQuery(start, end, right_son(p), mid + 1, right));
            }
            
        }

        return result;
    }

    int rangeQuery(int start, int end) {
        if (start > end) {
            return -1;
        }
        if (start < 0 || end >= _tree_source.size()) {
            return -1;
        }

        return _rangeQuery(start, end, 1, 0, _tree_source.size() - 1);

    }
private:
    std::vector<int> _tree_result;
    const std::vector<int> _tree_source;
    NORMAL_OPERATION_FUNC _normal_func;
};