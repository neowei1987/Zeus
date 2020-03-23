
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

/***************分治策略之二分查找**************/

class Solution {
public:
    int binary_find(int* nums, int n, int k) {
        int l = 0;
        int h = n - 1;
        while (l < h) {
            int m = l + ((h - l) >> 1);
            if (nums[m] == k) {
                return m;
            }
            else if (nums[m] < k) {
                l = m + 1;
            }
            else {
                h = m - 1;
            }
        }

        if (nums[l] != k) {
            return -1;
        }

        return l;
    }

    //旋转数组查找“旋转点”
    int rotate_find_pivot(vector<int>& data, int &index) {
        int l = 0;
        int h = data.size() - 1;
        //循环何以继续？ 
        while (data[l] >= data[h]) { //如果最左边的小于最右边的了，则说明；
            if (h - l == 1)  { //如果相差只有1了，类似于【5，4】则直接返回h
                index = h;
                return data[h];
            }

            int m = l + ((h - l) >> 1);
            if (data[m] == data[l] && data[m] == data[h]) { //都相等
            
                int min = data[h];
                index = h;
                for (int i = h - 1; i >= l + 1; --i) {
                    if (data[i] <= min) {   //对应两种场景：1. 全部相等 2. 相等，后增加的case 22222222220122222222222的场景
                        min = data[i];
                        index = i;
                    }
                    if (data[i] < data[i - 1]) {//先增加，后相等的case  2222222234522222222的情况，
                        min = data[i];
                        index = i;
                        return min;
                    }
                }

                return min;
            }

            if (data[m] >= data[l]) { //一定在后半部分，考虑13，21， 1，2
                l = m + 1; l = m;//都可以
            }
            else if (data[m] <= data[h]){ //考虑10,3,4的情况，如果h=m-1;会错过最小值
                h = m; //只能
            }
            //other case (m<left && m > right) 21,12,10? 这种情况不可能出现的
        }
    
        index = l;
        return data[l];
    }

    int binary_find_with_mod(vector<int>& nums, int begin, int k) {
        int l = 0;
        int n = nums.size();
        int h = n - 1;

        while (l < h) {
            int m = l + ((h - l) >> 1);
            int real_m = (m + begin )%n;
            if (nums[real_m] == k) {
                return (m + begin) %n;
            }
            else if (nums[real_m] < k) {
                l = m + 1;
            }
            else {
                h = m - 1;
            }
        }

        if (nums[(l + begin) % n] != k) {
            return -1;
        }

        return (l+begin) %n;
    }

    int searchInRotateArray(vector<int>& nums, int target) {
        if (nums.empty())
            return false;
        int min_idx = 0;
        int min = rotate_find_pivot(nums, min_idx);
        cout << "min:" << min << ",idx:" << min_idx << "size:" << nums.size() << endl;
        return binary_find_with_mod(nums, min_idx, target) == -1 ? false : true;
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
    problem.searchInRotateArray(popped, 10);

	return 0; 
} 
