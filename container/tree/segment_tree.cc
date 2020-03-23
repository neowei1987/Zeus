#include "segment_tree.h"
#include "sstream"
#include "iostream"
#include "vector"
#include "stack"
using namespace std;

std::istream& operator >> (std::istream& in, std::vector<int>& target) {
    char c;
    in >> c;
    while (true) {
        int num = 0;
        char comma = ']';
        in >> num >> comma;
        target.push_back(num);
        if (comma == ']') {
            break;
        }
    }
    return in;
}

int min_idx(const std::vector<int>& data, int idx1, int idx2) {
    if (data[idx1] < data[idx2]) {
        return idx1;
    }
    else {
        return idx2;
    }
}

class Solution {
public:
  int _largestRectangleArea(vector<int>& heights, int left, int right) {
        //base
        if (left > right) {
            return 0;
        }
        if (left == right) {
            return heights[left];
        }

        /*
        int lowest_val = heights[left]; //考虑如果有多个lowest_val, 我们应该尽量取在中间
        vector<int> lowest_idxs;
        lowest_idxs.push_back(left);
        for (int i = left + 1; i <= right; ++i) {
            if (heights[i] <= lowest_val) {
                if (heights[i] != lowest_val) {
                    lowest_idxs.clear();
                }
                lowest_idxs.push_back(i);
                lowest_val = heights[i];
            }
        }
        //取中间的最小值
        int mid_lowest = lowest_idxs[lowest_idxs.size() / 2];
        */

        int mid_lowest = _seg_tree->rangeQuery(left, right);
        int lowest_val = heights[mid_lowest];
        cout << "find_lowest in range[" << left << "~" << right << "], ret:" << mid_lowest << endl;

        //左半部分
        int left_max = _largestRectangleArea(heights, left, mid_lowest - 1); //注意mid-1
        //右半部分
        int right_max = _largestRectangleArea(heights, mid_lowest + 1, right);
        //合并 [注意不要用成mid_lowest]
        return std::max(lowest_val * (right - left + 1), std::max(right_max, left_max));

    }   

    static int min_func(const vector<int>& data, int idx1, int idx2) {
        if (data[idx1] < data[idx2]) {
            return idx1;
        }
        else {
            return idx2;
        }
    }

    int largestRectangleArea(vector<int>& heights) {
        _seg_tree = new SegmentTree(heights, min_func);
        return _largestRectangleArea(heights, 0, heights.size() - 1);
    }

    int largestRectangleAreaWithStack(vector<int>& heights) {
        int max_area = 0;
        std::stack<int> s;
        s.push(-1); //哨兵元素
        for (int i =0; i <heights.size(); ) {
            while (s.top() != -1 && heights[s.top()] > heights[i]) {
                int k = s.top(); 
                s.pop();
                max_area = std::max(max_area, (i - s.top() - 1) * heights[k]);
            }
            s.push(i++);
        }

        while (s.top() != -1) {
            int k = s.top();
            s.pop();
            max_area = std::max(max_area, ((int)heights.size() - s.top() - 1) * heights[k]);
         }

        return max_area;
    }

private:
    SegmentTree* _seg_tree;
};

int main() 
{ 
    std::stringstream ss;
    ss << "[6,7,5,2,4,5,9,3]";
    std::vector<int> nums;
    ss >> nums;
    Solution s1;
    std::cout << nums.size() << "\t" << s1.largestRectangleAreaWithStack(nums) << "\n";
    /*
    SegmentTree st(nums, min_idx);
    std::cout << nums[st.rangeQuery(0, nums.size() - 1)] << std::endl;  
    */
}