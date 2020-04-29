
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "defines.h"

using namespace std;

class Solution {
public:
    /*
    vector<vector<int> > threeSum(vector<int>& nums) {
        //借助Hash, 两数之和优化到O(N);
        //同样，三数之和可以优化到O(N^2)
        //时间复杂度已经超过O(n*lgn)，所以考虑对数组进行排序，排序之后是否可以优化
        //排序后，可以使用双指针
    }
    */

    //对撞指针
    int removeNum(vector<int>& elems, int x) {
        if (!elems.size()) {
            return 0;
        }

        int i = 0; 
        int n = elems.size();
        int j = n;
        while (i < j) {
            if (elems[i] == x) {
                elems[i] = elems[--j];
                n--;
            }
            else {
                i++;
            }
        }
        return n;
    }

    //快慢指针
    int removeDuplicates(vector<int>& nums) {
        if (!nums.size()) {
            return 0;
        }
        int i = 0; 
        for (int j = 1; j < nums.size(); ++j) {
            if (nums[j] != nums[i]) {
                ++i;
                nums[i] = nums[j];
            }
        }

        return i + 1;
    }

};

int main(int argc, char* argv[]) 
{ 
    std::vector<int> data;
    std::stringstream ss;
    ss << argv[1];
    ss >> data;

    Solution problem;
        //cout << "result: " << problem.removeNum(data, 3) << "\n" << data << endl;
        cout << "result: " << problem.removeDuplicates(data) << "\n" << data << endl;

	return 0; 
} 




/*
对动态未来形式的预判
比线性来的更快
*/

 int longestSubstringWithoutDuplication(string s) {
        map<char, int> counter;
        
        int i = 0, j = 0;
        int mw = 1;
        while (j < s.size()) {
            if (counter[s[j] == 0) {
                counter[s[j]++;
                j++;
                mw = max(mw, j - i + 1);
            }
            else {
                counter[s[i]--;
                i++;
            }
        }
        return mw;
    }

    char firstNotRepeatingChar(string s) {
        map<char, int> counter;
        for (auto x: s) {
            counter[x]++;
        }
        for (auto x: s) {
            if (counter[x] == 1) {
                return x;
            }
        }

        return '#';
    }


struct list_node {
    char ch;
    bool del;
    list_node* next;
    list_node* pre;

    list_node(char _ch) {ch = _ch; next = this; pre = this; del=false;}
};

list_node* head;
list_node* tail;

class Solution{
public:
    map<char, list_node* > counter;

    //Insert one char from stringstream
    void insert(char ch){
        if (!head) {
            tail = head = new list_node('#');
        }
    
        auto t = counter.find(ch);
        if (t == counter.end()) {
            //cout << "insert into list: " << ch << ", pre: " << tail->ch << endl;
            auto node = new list_node(ch);
            counter.insert({ch, node});
            node->next = tail->next;
            node->pre = tail;
            tail = tail->next = node;  
        }
        else {
            //cout << "delete from list: " << ch << endl;
            auto del_node = t->second;
            if (del_node->del) {
                return;
            }
            del_node->del = true;
            del_node->pre->next = del_node->next;
            del_node->next->pre = del_node->pre;
            if (del_node == tail) {
                if (del_node->pre != head) {
                    tail = del_node->pre;
                }
                else {
                    tail = del_node->next;
                }
            }
        }
    }

    //return the first appearence once char in current stringstream
    char firstAppearingOnce(){
        if (!head) return '#';
        return head->next->ch;
    }
};

class Solution {
public:
    vector<int> nums;
    vector<int> cp;
    int cnt;

    void merge(int l, int m, int r) {
        int k = l;
        while (k <= r) {
            cp[k] = nums[k];
            k++;
        }

        int i = l;
        int j = m + 1;
        k = l;

        while (i <= m && j <= r) {
            if (cp[i] <= cp[j]) 
            {
                nums[k++] = cp[i++];
            }
            else {
                cnt += (m - i + 1);
                nums[k++] = cp[j++];
            }
        }

        while (i <= m) {
            nums[k++] = cp[i++];
        }
        while (j <= r) {
            nums[k++] = cp[j++];
        }
    }

    void dfs(int l, int r) {
        if (l == r) return;
        int mid = l + r >> 1;
        dfs(l, mid);
        dfs(mid + 1, r);
        merge(l, mid, r);
    }

    int inversePairs(vector<int>& _nums) {
        if (_nums.empty()) return 0;
        nums = _nums;
        cnt = 0;
        cp.resize(nums.size());
        dfs(0, nums.size() - 1);
        return cnt;
    }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *findFirstCommonNode(ListNode *h1, ListNode *h2) {
       int c1 = 0, c2 = 0;
       for (auto p = h1; p; p = p->next) c1++;
       for (auto p = h2; p; p = p->next) c2++;
       
       auto p1 = h1;
       auto p2 = h2;
        while (c2 < c1) {
            p1 = h1 = h1->next;
            c2++;
        }
        while (c1 < c2) {
            p2 = h2 = h2->next;
            c1++;
        }

       while (p1 && p2 && p1 != p2) {
           p1 = p1->next;
           p2 = p2->next;
       }

       return p1;
    }
};

int getNumberOfK(vector<int>& nums , int k) {
    if (nums.empty())  return 0;
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (nums[mid] < k) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    if (nums[r] != k) return 0;
    int left = r;

    l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = l + r  + 1 >> 1;
        if (nums[mid] > k) {
            r = mid - 1;
        }
        else {
            l = mid;
        }
    }

    return r - left + 1;
}


    int getMissingNumber(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for (auto x: nums) {
            sum += x;
        }  
        return (n * (n + 1) >> 1) - sum;
    }

    int k = 0;

    TreeNode* dfs(TreeNode* root) {
        if (root->left) {
            auto r = dfs(root->left);
            if (r) return r;
        }
        if (--k == 0) return root;

        if (root->right) return dfs(root->right);
        return nullptr;
    }

    TreeNode* kthNode(TreeNode* root, int _k) {
        k = _k;
        return dfs(root);    
    }


    int dfs(TreeNode* root, int d) {
        if (!root) return 0;
        return 1 + max(dfs(root->right), dfs(root->left));

    }
    int treeDepth(TreeNode* root) {
        return dfs(root);
    }

    typedef pair<bool, int> PBI;

    PBI dfs(TreeNode* root) {
        if (!root) return {true, 0};

        auto lbi = dfs(root->left);
        if (!lbi.first) return {false, 0};

        auto rbi = dfs(root->right);
        if (!rbi.first) return {false, 0};

        return abs(lbi.second - rbi.second) > 1  ? {false, 0} : {true, 1 + max(bi.second, rbi.second)};

    }

    bool isBalanced(TreeNode* root) {
        return dfs(root).first;
    }

    vector<int> findNumsAppearOnce(vector<int>& nums) {
        int s = 0;
        for (auto x: nums) {
            s ^= x;
        }

        int u = s & -s;
        vector<int> g0, g1;

        for (auto x: nums) {
            if (x & u ) g1.push_back(x);
            else g0.push_back(x); 
        }

        vector<int> res(2, 0);
        for (auto x : g0) {
            res[0] ^= x;
        }
        for (auto x : g1) {
            res[1] ^= x;
        }

        return res;
    }

    int findNumberAppearingOnce(vector<int>& nums) {
        vector<int> bitmap(32, 0);
        for (auto x: nums) {
            for (int i = 0; i < 32; ++i) {
                if (x & (1 << i)) bitmap[i]++;
            }
        }
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            if (bitmap[i] % 3) {
                res += 1 << i;
            }
        }
        return res;
    }

    vector<int> findNumbersWithSum(vector<int>& nums, int target) {
        unsorted_hash<int, int> hash;
        for (int i = 0; i < nums.size(); ++i) {
            hash[nums[i]] = i;
        }
        vector<int> res(2, 0);
        for (int i = 0; i < nums.size(); ++i) {
            auto r = hash.find(target - nums[i]);
            if (r != hash.end()) {
                res[0] = i;
                res[1] = r->second;
            }
        }
        return res;
    }

    vector<vector<int> > findContinuousSequence(int t) {
        //1+2+3+4+5=4+5+6=7+8=15，所以结果打印 
        int i = 1, j = 1;
        int sum = 0;
        vector<vector<int> > res; //[i, j-1]的和
        while (j < t) {
            if (sum >= t) {
                while (sum > t) {
                    sum -= i;
                    i++;
                }
                if (sum == t) {
                    int p = i;
                    vector<int> one;
                    while (p <= j - 1) {
                        one.push_back(p);
                    }
                    res.push_back(one);
                }
            }
            else {
                sum += j;
                j++;
            }
        }  

        return res; 
    }