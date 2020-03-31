
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
#include "queue"
#include <map>
using namespace std; 

/*****************滑动窗口**********************/

class Solution {
public:
    string minWindow(string src, string tt) {
        //S = "ADOBECODEBANC", T = "ABC"
        //输出: "BANC"
        vector<int> counter(256, 0);
        const char* s = src.c_str();
        const char* t = tt.c_str();

        while (*t) {
            counter[*t]++;
            t++;
        } 
        
        while (*s) {
            if (*s == *t) {
                s++;
                t++;
            }
            else {
                s++;
            }
        }

        return "";
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
    ss << "[7,5,6,4]";
    ss >> popped;

    Solution problem;
    cout << "result: " << problem.minWindow(argv[1], argv[2]) << "\n";

	return 0; 
} 
