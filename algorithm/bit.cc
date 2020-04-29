
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

const int N = 10000;
int f[N];

class Solution {
public:
    int find(int x) {
        while (x != f[x]) x = f[x];
        return x;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        for (auto x : edges) {
            f[x[0]] = x[0];
            f[x[1]] = x[1];
        }

        vector<int> res; 
        for (auto x : edges) {
            int p0 = find(x[0]);
            int p1 = find(x[1]);
            if (p0 != x[0] && p1 != x[1]) {
                return x;
            }

            f[x] = p0;
        }  

        return res;
    }
};

class Solution {
public:
       /***********位操作***************/
    int countDigitOne(int n) {
        return 0;
        // n&(n-1)     
    }

    //判断一个数是不是 2 的指数
    bool isPowOf2(int x) {
         // n&(n-1)
    }

    //判断两个整数是否异号
    bool isDiff(int x, int y) {
        return ((x ^ y) < 0); // true
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
