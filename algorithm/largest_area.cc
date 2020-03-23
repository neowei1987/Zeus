
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

class Solution {
public:

    /***********最大矩形面积***************/

    int _largestRectangleArea(vector<int>& heights, int left, int right) {
        //base
        if (left > right) {
            return 0;
        }
        if (left == right) {
            return heights[left];
        }

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
        //左半部分
        int left_max = _largestRectangleArea(heights, left, mid_lowest - 1); //注意mid-1
        //右半部分
        int right_max = _largestRectangleArea(heights, mid_lowest + 1, right);
        //合并 [注意不要用成mid_lowest]
        return std::max(lowest_val * (right - left + 1), std::max(right_max, left_max));

    }   
    int largestRectangleArea(vector<int>& heights) {
        /*
        //Time: O(N^2),  Space: O(N^2)
        int n = heights.size();
        vector< vector<int> > dp;
        dp.reserve(n);
        for (int i = 0; i < n; ++i) {
            dp[i].reserve(n);
            dp[i][i] = heights[i];
        }

        int max = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                dp[i][j] = std::min(dp[i][j -1], heights[j]);
                max = std::max(max, (j - i + 1) * dp[i][j]);
            }
        }    
        return max;   
        */

        /*
        //Time: O(N^3),  Space: O(1)
        int n = heights.size();
        int max = n == 0 ? 0 : heights[0];
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int min = heights[i];
                for (int k = i; k <= j; ++k) {
                    min = std::min(min, heights[j]);
                }
                max = std::max(max, (j - i + 1) * min);
            }
        }   
        return max; 
        */
     
        /*
        //Time: O(N^2),  Space: O(1)
        int n = heights.size();
        int max = 0;
        for (int i = 0; i < n; ++i) {
            int min = INT_MAX;
            //比较容易想到的动规方程：dp[i,j] = min(dp[i][j - 1], heights[j])
            //注意到每次只跟前面的值有关，所以可以专用一个变量来保存，从而节省更多的空间；
            for (int j = i; j < n; ++j) {
                min = std::min(min, heights[j]);
                max = std::max(max, (j - i + 1) * min);
            }
        } 
        return max; 
        */

       /*
        分治法：
        如何划分子问题？ 二分或者其他？ 划分的标准是什么？
        一般性原则：基于某种划分规则，子问题应该很容易合并起来
        子问题（也就是退出条件要考虑清楚）
        return _largestRectangleArea(heights, 0, heights.size() - 1);
       */

      /*
      考虑下可能出现的最坏情况，如果数组是有序的；每次问题规模只能减去1；所以最后的时间复杂度会退化为O(N^2)
      T(n) = T(n - 1) + T(1) + n = n + (n-1) + ... + 1 = O(N^2)
      考虑能否找最小值的算法优化一波？ 
      问题转化为：给你一个数组，求解区间[i,j]的最小值；该问题可以通过线段树去解决。
      */
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
