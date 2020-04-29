
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

/***************回溯问题***************/

class Solution {
public:
      void _printNumbers(int depth, int max_depth, char* numbers, vector<string>& result) {
        if (depth == max_depth) {
            fprintf(stderr, "%s\n", numbers);
            return;
        }
        for (int i = 0; i < 10; ++i) {
            numbers[depth] = '0' + i;
            _printNumbers(depth + 1, max_depth, numbers, result);
        }
    }

    vector<string> printNumbers(int n) {
        vector<string> result;
        char* numbers = new char[n + 1];
        numbers[n] = '\0';

        int depth = 0;
        int max_depth = n;
        for (int i = 0; i < 10; ++i) {
            numbers[depth] = '0' + i;
            _printNumbers(depth + 1, max_depth, numbers, result);
        }

        delete []numbers;
        return result;
    }

    void _permute(vector<int>& nums, int idx, vector<vector<int> >&result) {
        if (idx == nums.size()) {
            result.push_back(nums);
            /*
            for (int i = 0; i < nums.size(); ++i) {
                cout << nums[i] << "\t";
            }
            cout << "\n";
            */
            return;
        }

        for (int i = idx; i < nums.size(); ++i) {
            std::swap(nums[idx], nums[i]);
            _permute(nums, idx + 1, result);
            std::swap(nums[idx], nums[i]);
        }
    }

    vector<vector<int> > permute(vector<int>& nums) {
        vector<vector<int> > result;
        int idx = 0;
        for (int i = idx; i < nums.size(); ++i) {
            std::swap(nums[idx], nums[i]);
            _permute(nums, idx + 1, result);
            std::swap(nums[idx], nums[i]);
        }
        return result;
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
