
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
#include <map>
using namespace std; 

/*
dfs
*/
class Solution {
public:
    void dfs(vector<vector<char>>& grid, int m, int n, int i, int j, vector<bool>& visit) {
         //方向数组
        pair<int, int> ds[4] = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1},
        };

        for (int di = 0; di < sizeof(ds) / sizeof(ds[0]); ++di) {
            int ni = i + ds[di].first;
            int nj = j + ds[di].second;
            if (ni >= 0 && ni < m && nj >= 0 && nj < n  //范围合法
                && grid[ni][nj] == '1'                //陆地
                && !visit[ni * n + nj]              //没有访问过
                ) {
                visit[ni * n + nj] = true;
                dfs(grid, m, n, ni, nj, visit);
            }
        }
    }

    //模型：最大连通子图数
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        if (m == 0) {
            return 0;
        }
        int n = grid[0].size();
        if (n == 0) {
            return 0;
        }

        vector<bool> visit(m * n, false);
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1' && !visit[i * n + j]) {
                    visit[i * n + j] = true;
                    count++;
                    dfs(grid, m, n, i, j, visit);
                }
            }
        }
        return count;
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
    ss << "[2]";
    ss >> popped;
    int ret = 0;

    Solution problem;
    //problem.printNumbers(5);
    //cout << problem.validateStackSequences(pushed, popped);
    //cout << problem.search(nums, k);
    //problem.permute(pushed);
    //cout << problem.majorityElement(popped);
    //problem.getLeastNumbers(popped, 0);
    ret = problem.coinChange(popped, 3);
    cout << "result: " << ret << "\n";

	return 0; 
} 
