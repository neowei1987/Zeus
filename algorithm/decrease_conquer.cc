
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

/*减治策略*/

class Solution {
public:
    bool searchMatrix(vector<vector<int> >& matrix, int target) {
        int h = matrix.size();
        if (h == 0) {
            return false;
        }
        int w = matrix[0].size();
        if (w == 0) {
            return false;
        }

        int i = 0;
        int j = w - 1;
        while (i < h && j >= 0 && matrix[i][j] != target) {
            if (matrix[i][j] > target) { 
                j--;
                continue;
            }

            if (matrix[i][j] < target) { 
                i++;
                continue;
            }
        }
        
        if (i >= h || j < 0) {
            return false;
        }
        return true;
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
