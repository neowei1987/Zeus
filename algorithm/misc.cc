
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

class Solution {
public:
    /*摩尔取数*/
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return nums[0]; 
        }

        int cnt = -1;
        int pre = 0;
        for (int i = 0; i < n; ++i) {
            if (cnt == -1) {
                pre = nums[i];
                cnt = 0;
                cout << "pre<=" << pre << endl;
            }

            if (pre == nums[i]) {
                cnt++;
            }
            else 
            {
                cnt--;
                if (cnt == 0) {
                    cnt = -1;
                }
            }
        }

        return pre;
    }

    /***********位操作***************/
    int countDigitOne(int n) {
        return 0;
    }

    /*****************双指针***************/
    vector<vector<int>> findContinuousSequence(int target) {

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
    cout << "result: " << popped << "\n";

	return 0; 
} 
