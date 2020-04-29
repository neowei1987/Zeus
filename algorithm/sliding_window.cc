
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
    bool isOK(vector<int>& counter) {
        for (int i = 0; i < counter.size(); ++i)  {
            if (counter[i] < 0) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string src, string tt) {
        //S = "ADOBECODEBANC", T = "ABC"
        //输出: "BANC"
        vector<int> counter(256, 0);
        vector<bool> needed(256, false);
        const char* l = src.c_str();
        const char* t = tt.c_str();

        //子串的模式信息
        int matched_cnt = tt.length();
        while (*t) {
            counter[*t]--;
            needed[*t] = true;
            t++;
        } 

        //如何判定当前的信息是否足够...
        int mw = src.length() + 1;
        const char* r = l;
        const char* ret = l;
        while (*r) {
            if (needed[*r]) {
                counter[*r]++;
                //cout << *r << "," << counter[*r] << ","<< " matched\n";
                r++;
            }
            else {
                r++;
                continue;
            }

            while (isOK(counter)) {
                if (mw > int(r - l)) {
                    mw = int(r - l);
                    ret = l;
                    //cout << string(ret, mw) << "ws:" << mw << endl;
                }
                if (needed[*l]) {
                    if (counter[*l] <= 0) {
                        break;
                    }
                    else {
                        counter[*l]--;
                        //cout << *l << "," << counter[*l] << ","<< " removed\n";
                    }
                }
                l++;
            }
        }

        if (isOK(counter)) {
            return string(ret, mw);
        }
        else {
            return "";
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
    ss << "[7,5,6,4]";
    ss >> popped;

    Solution problem;
    cout << "result: " << problem.minWindow(argv[1], argv[2]) << "\n";

	return 0; 
} 


