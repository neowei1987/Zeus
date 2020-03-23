
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

/*数组rotated*/

class Solution {
public:

    // Return the maximum hamming distance of a rotation 
    int maxHamming(int arr[], int n) 
    { 
        // We know hamming distance with 0 rotation 
        // would be 0. 
        int maxHam = 0;	 

        // We try other rotations one by one and compute 
        // Hamming distance of every rotation 
        for (int i = 1; i < n; i++) 
        { 
            int currHam = 0; 
            for (int j = i, k=0; j < (i + n); j++,k++) 
                if (arr[j%n] != arr[k]) 
                    currHam++; 

            // We can never get more than n. 
            if (currHam == n) 
                return n; 

            maxHam = max(maxHam, currHam); 
        } 

        return maxHam; 
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
