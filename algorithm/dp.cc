
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

//最小编辑距离
可能还会问，这里只求出了最小的编辑距离，那具体的操作是什么？你之前举的修改公众号文章的例子，只有一个最小编辑距离肯定不够，还得知道具体怎么修改才行。
这个其实很简单，代码稍加修改，给 dp 数组增加额外的信息即可：
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

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) {
            return 0;
        }
        vector<int> dp(n, 0);
        int profit = 0;
        int min = INT_MAX;;
        for (int i = 1; i < n; ++i) {
            min = std::min(min, prices[i]);
            dp[i] = std::max(dp[i -1], prices[i] - min);
            profit = std::max(dp[i], profit);
        }

        return profit;
    }

    //coins = [1, 2, 5], amount = 11
    int _coinChange(const vector<int>& coins, vector<int>& dp, int amount) {
        //cout << "begin amount: " << amount << " dp:" << dp << endl;
        if (dp[amount] != 0) { //被计算过
            return dp[amount];
        }

        int min_cnt = INT_MAX;
        for (int i = 0; i < coins.size(); ++i) {
            if (amount > coins[i]) {
                int ret = _coinChange(coins, dp, amount - coins[i]);
                if (ret != -1) {
                    min_cnt = std::min(ret, min_cnt);
                }
            }
        }

        if (min_cnt == INT_MAX) {
            dp[amount] = -1;
        }
        else {
            dp[amount] = min_cnt +1;
        }

        //cout << "amount: " << amount << " dp:" << dp << endl;
        return dp[amount];
    }

    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) {
            return 0;
        }

        vector<int> dp(amount + 1, 0);
        for (int i = 0; i < coins.size(); ++i) {
            if (coins[i] == amount) {
                return 1;
            }
            else if (coins[i] < amount) {
                dp[coins[i]]  = 1;
            }
        }
    
        return _coinChange(coins, dp, amount);
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
    ss << "[2]";
    ss >> popped;
    int ret = 0;

    Solution problem;
    //problem.printNumbers(5);
    //cout << problem.validateStackSequences(pushed, popped);
    //cout << problem.search(nums, k);
    //problem.permute(pushed);
    //cout << problem.majorityElement(popped);
    //problem.getLeastNumbers(popped, 0);
    ret = problem.coinChange(popped, 3);
    cout << "result: " << ret << "\n";

	return 0; 
} 
