
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

class Solution {
public:
    /*摩尔取数*/
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return nums[0]; 
        }

        int cnt = -1;
        int pre = 0;
        for (int i = 0; i < n; ++i) {
            if (cnt == -1) {
                pre = nums[i];
                cnt = 0;
                cout << "pre<=" << pre << endl;
            }

            if (pre == nums[i]) {
                cnt++;
            }
            else 
            {
                cnt--;
                if (cnt == 0) {
                    cnt = -1;
                }
            }
        }

        return pre;
    }

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.empty()) return res;
        int m = matrix.size();
        int n = matrix[0].size();
        int size =  m * n;
        PII dx[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        vector<bool> visited(size, false);
        
        for (int k = 0, i = 0, j = 0, d = 0; k < size; ++k) {
            res.push_back(matrix[i][j]);
            visited[i * n + j] = true;
            i += dx[d].first;
            j += dx[d].second;
            if (i < 0 || i >= m || j < 0 || j >= n || visited[i * n + j]) {
                i -= dx[d].first;
                j -= dx[d].second; 
                d = (d + 1) % 4;
                i += dx[d].first;
                j += dx[d].second;  
            }
        }

        return res;
    }

    typedef pair<int, int> PII;

    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> f(m, vector<int>(n, 0));
        f[0][0] = grid[0][0] ? 1 : 0;
        if (!f[0][0]) return 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j >= 1 && grid[i][j - 1] == 1) {
                    f[i][j] = 1 + f[i][j - 1];
                }
                else if (i >= 1 && grid[i - 1][j] == 1) {
                    f[i][j] = 1 + f[i - 1][j];
                }
            }
        }
        return f[m - 1][n - 1];
    }

    int rob(vector<int>& nums) {
        /*
        f(i）表示所有以nums[i]结尾的方案所获得金额的集合；集合元素的最大值    
        */
       int n = nums.size();
       if (!n) return 0;
       vector<int> f(n + 2, 0);
       for (int i = 0; i < n; ++i) {
            f[i + 2] = max(nums[i] + f[i], f[i + 1]);
       }
       return f[n + 1];
    }

    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        vector<int> f(n, 1);
        int res = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[j] < nums[i]) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }
            res = max(res, f[i]);
        }
       return res;
    }

    int minDistance(string a, string b) {
        int m = a.size();
        int n = b.size();
        
        vector<vector<int>> f(m + 1, vector<int>(n + 1, INT_MAX));
        f[0][0] = 0;
        for (int i = 0; i < n; ++i) {
            f[0][i] = i;
        }
        for (int i = 0; i < m; ++i) {
            f[i][0] = i;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i] == b[j]) {
                    f[i + 1][j + 1] = f[i][j];
                }
                else {
                    f[i + 1][j + 1] = 1 + min(f[i][j], f[i][j+1], f[i+1][j]);
                }
            }
        }

        return f[m][n];
         
        /*
        相等
        a[i] == b[j] f[i - 1][j - 1]
        不等
        修改a,或者修改b 1+ f[i - 1][j - 1]
        a中删除一个字符 1 + f[i - 1][j]
        b中删除一个字符 1 + f[i][j - 1]
        a中插入一个字符b[j] 1 + f[i][j - 1] 
        b中插入一个字符a[i] 1 + f[i - 1][j]
        */

    }

    vector<int> fa;

    int find(int x) {
        while (x != fa[x]) {
            x = fa[x];
        }
        return x;
    }

    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        fa.resize(n);

        for (int i = 0; i < n; ++i) {
            fa[i] = i;
        }    

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                if (find(i) != find(j) && M[i][j]) {
                    fa[find(i)] = j;
                }
            }
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += fa[i] == i;
        }
        return res;
    }

    /*****************双指针***************/
    vector<vector<int> > findContinuousSequence(int target) {
        return vector<vector<int> >();
    }  

      //因为有序，可以考虑二分优化
    int binaryFind(vector<int>& nums, int t, int left, int right) {
        //顺序查找，找到第一个大于t的元素
        for (int i = right; i >= left; i--) {
            if (nums[i] > t) {
                return i;
            }
        }
        assert(0);
        return left;
    }

    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1)   {
            return;
        }  
    
        int i = 0;
        for (i = n - 1; i >= 0; i--) {
            if (i + 1 >= n || nums[i] >= nums[i + 1]) //如果前面的元素大于当前元素
            {
                continue;
            }

            //i变小了； （i + 1, n -1)
            int t = binaryFind(nums, nums[i], i + 1, n - 1);
            fprintf(stderr, "binaryFind [%d-%d] target:%d, ret:%d\n", i + 1, n - 1, nums[i], t);
            //cout << nums << endl;
            std::swap(nums[i], nums[t]); 
            //cout << nums << endl;
            break;
        }

        //swap from [++i ~ n - 1]
        ++i;
        int left = ++i;
        int right = n - 1;
        while (left < right) {
            std::swap(nums[left++], nums[right--]);
        }
    }

};

vector<int> sum;
int target = 0;

bool dfs(vector<int>& nums, int u) {
    if (u == nums.size()) {
        return sum[0] == sum[1] && sum[1] == sum[2] && sum[2] == sum[3] && sum[0] == target;
    }

    for (int i = 0; i < 4; ++i) {
        if (nums[u] > target - sum[i]) {
            continue;
        }
        
        sum[i] += nums[i];
        if (dfs(nums, u + 1)) {
            return true;
        }
        sum[i] -= nums[i];
    }
    return false;
}

bool makesquare(vector<int>& nums) {
    long sum = 0;
    for (auto x : nums) {
        sum += x;
    }

    target = sum / 4;
    if (sum != 4 * target) return false;

    return dfs(nums, 0);
}

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        if (!n) return 0;

        int sum = A[0];
        for (int i = 1; i < 2 * n; ++i) {
            if (sum < 0) {
                sum = A[i % n];
            }
            else {
                sum += A[i %n ];
            }
        }

        return sum;
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
    ss << "[1,3,2]";
    ss >> popped;

    Solution problem;
    //problem.printNumbers(5);
    //cout << problem.validateStackSequences(pushed, popped);
    //cout << problem.search(nums, k);
    //problem.permute(pushed);
    //cout << problem.majorityElement(popped);
    cout << "result: " << popped << "\n";

	return 0; 
} 
