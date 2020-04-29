
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

    //https://www.cnblogs.com/sdlwlxf/p/5131793.html

    int _partition(vector<int>& nums, int left, int right) {
        int p = nums[left];
        int l = left;
        int r = right + 1;
        while (true) {
            //必须放在前面；因为前面r== right+1; 所以l必定小于r; r必定会--；
            //反过来， 如果把第二段放到前面，当left=right的话，l++会导致程序break;
            while (l < r && (cout << r << endl, 1) && nums[--r] > p) {} 
            if (l >= r) {
                break;
            }

            while (l < r && nums[++l] <= p) {}
            if (l >= r) {
                break;
            }

            swap(nums[l], nums[r]);
        }

        //经过上面的循环，有两种情况：
        //l->12, 9<-r; 交换之后，r->9, l->12; 此时必须交换9；
        //1->12, 11, 9<-r; 交换之后，r->10<-l； 此时l=r；
        swap(nums[left], nums[r]);
        return r;
    }

    void _quickSort(vector<int>& nums, int l, int r) {
        if (l >= r) {
            return;
        }

        int p = _partition(nums, l, r);
        //cout << p << "[" << l << "~" << r <<"], datas:" << nums << endl;
        _quickSort(nums, l, p - 1);
        _quickSort(nums, p + 1, r);
    }

     vector<int> sortArray(vector<int>& nums) {
        _quickSort(nums, 0, nums.size() - 1);
        return nums;
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
    ss << "[" << argv[1] << "]";
    ss >> popped;

    Solution problem;
    //problem.printNumbers(5);
    //cout << problem.validateStackSequences(pushed, popped);
    //cout << problem.search(nums, k);
    //problem.permute(pushed);
    //cout << problem.majorityElement(popped);
    //problem.getLeastNumbers(popped, 0);
    problem.sortArray(popped);
    cout << "result: " << popped << "\n";

	return 0; 
} 
