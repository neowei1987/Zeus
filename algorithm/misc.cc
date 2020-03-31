
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

    /*****************双指针***************/
    vector<vector<int> > findContinuousSequence(int target) {
        return vector<vector<int> >();
    }  

      //因为有序，可以考虑二分优化
    int binaryFind(vector<int>& nums, int t, int left, int right) {
        //顺序查找，找到第一个大于t的元素
        for (int i = right; i >= left; i--) {
            if (nums[i] > t) {
                return i;
            }
        }
        assert(0);
        return left;
    }

    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1)   {
            return;
        }  
    
        int i = 0;
        for (i = n - 1; i >= 0; i--) {
            if (i + 1 >= n || nums[i] >= nums[i + 1]) //如果前面的元素大于当前元素
            {
                continue;
            }

            //i变小了； （i + 1, n -1)
            int t = binaryFind(nums, nums[i], i + 1, n - 1);
            fprintf(stderr, "binaryFind [%d-%d] target:%d, ret:%d\n", i + 1, n - 1, nums[i], t);
            //cout << nums << endl;
            std::swap(nums[i], nums[t]); 
            //cout << nums << endl;
            break;
        }

        //swap from [++i ~ n - 1]
        ++i;
        int left = ++i;
        int right = n - 1;
        while (left < right) {
            std::swap(nums[left++], nums[right--]);
        }
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
    ss << "[1,3,2]";
    ss >> popped;

    Solution problem;
    //problem.printNumbers(5);
    //cout << problem.validateStackSequences(pushed, popped);
    //cout << problem.search(nums, k);
    //problem.permute(pushed);
    //cout << problem.majorityElement(popped);
    problem.nextPermutation(popped);
    cout << "result: " << popped << "\n";

	return 0; 
} 
