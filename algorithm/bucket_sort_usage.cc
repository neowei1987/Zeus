
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

/*桶排序以及其变种应用*/

class Solution {
public:
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

    /*
    错误的做法，仅仅对nums元素为0～9时有效
    */
    void nextPermutationBad(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1)   {
            return;
        }  

        vector<int> counter(10, 0);
        
        //递增查找
        int i = 0;
        for (i = n - 1; i >= 0; i--) {
            counter[nums[i]]++;
            if (i + 1 >= n || nums[i] >= nums[i + 1]) //如果前面的元素大于当前元素
            {
                continue;
            }

            //i变小了； （i + 1, n -1)
            int t = binaryFind(nums, nums[i], i + 1, n - 1);
            fprintf(stderr, "binaryFind [%d-%d] target:%d, ret:%d\n", i + 1, n - 1, nums[i], t);
            cout << counter << endl;
            counter[nums[t]]--; 
            cout << nums << endl;
            std::swap(nums[i], nums[t]); 
            cout << nums << endl;
            cout << counter << endl;

            break;
        }

        cout << "sss" << i << endl;
        for (int k = 0; k < 10; k++) {
            int p = 0;
            while (p++ < counter[k]) {
                nums[++i] = k;
            }
        }
    }
};

int main(int argc, char* argv[]) 
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
    ss << argv[1];
    ss >> popped;

    Solution problem;
    problem.nextPermutation(popped);
    cout << "result: " << popped << "\n";

	return 0; 
} 
