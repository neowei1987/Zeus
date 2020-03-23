
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

class Solution {
public:

    /***********动态规划*********/

    /*
    经典动态规划问题，以下是状态转移方程：
    if dp[i - 1] >= 0, dp[i] = dp[i - 1] + nums[i];
    if dp[i - 1] < 0 || i = 0, dp[i] = nums[i]
    其中dp[i]表示以i为结尾的连续子数组最大和；
    另外，空间的压缩；由于dp[i]仅与前值有关，所以只需要一个变量就好，不需要一个数组
    */
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        int dp = nums[0];
        int max = dp;
        for (int i = 1; i < nums.size(); ++i) {
            if (dp >= 0) {
                //dp[i] = dp[i - 1] + nums[i];
                dp += nums[i];
                max = std::max(max, dp);
            }
            else {
                dp = nums[i];
                max = std::max(max, dp);
            }
        }

        return max;
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
