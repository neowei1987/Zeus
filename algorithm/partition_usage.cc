
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

/*快速排序思想应用partition*/

class Solution {
public:
     //如果按照其他方式来进行排序呢？
    vector<int> exchange(vector<int>& nums) {
        int left = 0;
        int right = nums.size() -  1;
        while (left < right) {
            while (left < right && nums[left] & 0x1) {
                left++;
            }
            while (right > left && !(nums[right] & 0x1)) {
                right--;
            }

            if (left != right) {
                int t = nums[right];
                nums[right] = nums[left];
                nums[left] = t;
                left++;
                right--;
            }
        }
        return nums;
    }
    
    //三色旗问题
    void sortColors(std::vector<int>& nums) {
        int idx = -1;
        int left = 0;
        int right = nums.size();

        while (left < right) {
            switch (nums[left]) {
                case 0: {
                    std::swap(nums[++idx], nums[left++]);
                    break;
                } 
                case 2: {
                    //很有可能swap过来之后是0， 或者1；
                    //如果是0的话，可能需要进一步处理
                    //如果是1的话，就ok了
                    std::swap(nums[--right], nums[left]); 
                    break;
                }
                case 1:
                    left++;
                    break;
            }
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
