
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

class Solution {
public:

    /*****************栈的应用**********************/

    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if (pushed.size() != popped.size()) {
            return false;
        }
        if (pushed.empty()) {
            return true;
        }
        int n =  pushed.size();
        stack<int> s;
        int i = 0;  //指向pop序列
        int k = 0;  //指向pushed序列
        s.push(-1);
        while (i < n) {
            cout << "compared:"  << popped[i] << " vs " << s.top() << endl;
            if (s.top() != popped[i]) {
                bool matched = false;
                for (; k < n; ++k) {
                    if (pushed[k] != popped[i]) {
                        cout << "pushed:"  << pushed[k] << endl;
                        s.push(pushed[k]);
                    }
                    else {
                        matched = true;
                        i++;
                        k++;
                        break;
                    }
                }
                if (!matched) {
                    if (k == n) {
                        return false;
                    }
                }
            }
            else {
                cout << "popped:"  << s.top() << endl;
                s.pop();
                
                i++;
            }
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
