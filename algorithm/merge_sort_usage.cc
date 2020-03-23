
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

class Solution {
public:

    //数组中的逆序对
    void merge(vector<int>& nums, int p1_left, int p1_right, int p2_left, int p2_right, int& ret) {
        /*
        哨兵方案，有一个问题：如果数组内容包含INT_MAX
        vector<int> p1;
        vector<int> p2;
        for (int i = p1_left; i <= p1_right; ++i) {
            p1.push_back(nums[i]);
        }
        p1.push_back(INT_MAX); 
        for (int i = p2_left; i <= p2_right; ++i) {
            p2.push_back(nums[i]);
        }
        p2.push_back(INT_MAX);  

        int i = 0;
        int j = 0;
        int k = p1_left;
        for (int k = p1_left; k <= p2_right; k++) {
            if (p1[i] <= p2[j]) { 
                nums[k] = p1[i++];
            }
            else {
                nums[k] = p2[j++];
                //如果左边的比右边的大，则增加逆序统计
                if (p1[i] != INT_MAX) {
                    ret += (p1.size() - 1 - k);
                }
            }
        }
        */
        vector<int> p1;
        vector<int> p2;
        for (int i = p1_left; i <= p1_right; ++i) {
            p1.push_back(nums[i]);
        }
        for (int i = p2_left; i <= p2_right; ++i) {
            p2.push_back(nums[i]);
        }

        int i = 0;
        int j = 0;
        int k = p1_left;
        for (k = p1_left; k <= p2_right && i < p1.size() && j < p2.size(); k++) {
            if (p1[i] <= p2[j]) { 
                nums[k] = p1[i++];
            }
            else {
                nums[k] = p2[j++];
                //如果左边的比右边的大，则增加逆序统计
                ret += (p1.size() - i);
                cout << p1 << "merge with " << p2 << " cnt:" << p1.size() - i << endl;
            }
        }

        //补齐剩下的数据（只补充数据，逆序数不需要额外再增加了）
        //p1到底，p2还有
        for (;j < p2.size(); j++) {
            nums[k++] = p2[j];
        }
        //p2到底，p1还有
        for (;i < p1.size(); i++) {
            nums[k++] = p1[i];
        }
    }

    void _reversePairs(vector<int>& nums, int left, int right, int& ret) {
        if (left == right) {
            return;
        }

        int mid = left + ((right - left) >> 1);
        _reversePairs(nums, left, mid, ret);
        _reversePairs(nums, mid + 1, right, ret);
        merge(nums, left, mid, mid + 1, right, ret);
    }

    int reversePairs(vector<int>& nums) {
        int ret = 0;
        _reversePairs(nums, 0, nums.size() - 1, ret);
        return ret;
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
