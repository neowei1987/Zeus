
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

/******************二叉树*******************/

class Solution {
public:

    bool _hasSameValue(TreeNode* A, TreeNode* B) {
        if (B == NULL) {
            return true;
        }
        if (A == NULL) {
            return false;
        }

         if (A->val != B->val) {
            return false;
         }

         return _hasSameValue(A->left, B->left) && _hasSameValue(A->right, B->right);
    }

    bool _isSubStructure(TreeNode* A, TreeNode* B) {
        if (A == NULL && B == NULL) {
            return true;
        }
        else if (A == NULL || B == NULL) {
            return false;
        }

        if (A->val == B->val) {
            return _hasSameValue(A->left, B->left) && _hasSameValue(A->right, B->right);
        }
        else {
            if (A->left) {
                if (_isSubStructure(A->left, B)) {
                    return true;
                }
            }
            if (A->right) {
                return _isSubStructure(A->right, B);
            }
            return false;
        }
    }   

    bool isSubStructure(TreeNode* A, TreeNode* B) {
        return _isSubStructure(A, B);
    }

    TreeNode* _mirrorTree(TreeNode* root) {
        if (NULL == root) {
            return NULL;
        } 

        TreeNode* mirror_right =_mirrorTree(root->right);
        TreeNode* mirror_left =  _mirrorTree(root->left);
        root->left = mirror_right;
        root->right = mirror_left;
        return root;
    }

    TreeNode* mirrorTree(TreeNode* root) {
        return _mirrorTree(root);
    }
    
   void _pathSum(TreeNode* root, int sum, vector<int>& path, vector<vector<int> > & result) {
        if (root == NULL) {
            return;
        }

        sum -= root->val;
        if (sum == 0) {
            if (root->left == NULL && NULL == root->right) {
                path.push_back(root->val);
                result.push_back(path);
                path.pop_back();
            }   
        }

        path.push_back(root->val);
        _pathSum(root->left, sum, path, result);
        _pathSum(root->right, sum, path, result);
        path.pop_back();
    }

    vector<vector<int> > pathSum(TreeNode* root, int sum) {
        vector<vector<int> >  ret;
        vector<int> path;
        _pathSum(root, sum, path, ret);
        return ret;
    }

    /*
    前序遍历 preorder = [3,9,20,15,7]
    中序遍历 inorder = [9,3,15,20,7]
    */
    TreeNode* buildTreeCore(vector<int>& preorder, vector<int>& inorder, 
        int pre_left, int pre_right, int in_left, int in_right) {

        if (pre_left > pre_right) {
            return NULL;
        }

        TreeNode* root = new TreeNode(preorder[pre_left]);
        //base condition
        if (pre_left == pre_right) {
            return root;
        }

        //scan到分割点
        int i = -1;
        int left_len = 0;
        for (i = in_left; i <= in_right; ++i) {
            if (inorder[i] == root->val) {
                break;
            }
            else {
                left_len++;
            }
        }
        if (i == -1) {
            throw new std::exception;
            return NULL;
        }

        if (left_len) { //如果有left child
            root->left = buildTreeCore(preorder, inorder, pre_left + 1, (pre_left + 1) + left_len - 1, in_left, i - 1);
        }

        if (pre_right - pre_left + 1 - 1 - left_len) {
            root->right = buildTreeCore(preorder, inorder, pre_left + left_len + 1, pre_right, i + 1, in_right);
        }
        
        return root;
    }

    //基于前序序列与中序序列构建树
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() != inorder.size() || preorder.empty()) {
            return NULL;
        }
        return buildTreeCore(preorder, inorder, 0, preorder.size() -1 , 0, inorder.size() - 1);
    }   

    /*
    typedef pair<int, int> PII;

    void dfs(TreeNode* root, PII single, PII& global) {
        if (!root) {
            global.first = std::max(global.first, single.first);
            return;
        };

        //如果遇到一个负节点
        if (root->val < 0) {
            global.second = std::max(global.second, single.second);
        }
        
        PII lg, rg;

        single.first += root->val;
        dfs(root->left, single, lg);
        dfs(root->right, single, rg);

        global.first = std::max();
    } 

    int maxPathSum(TreeNode* root) {
        if (!root) {
            return 0;
        }

        PII global, cur;
        global.first = INT_MIN;
        cur.first = 0;
        dfs(root, cur, global);
    }
    */

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root->val == p->val || root->val == q->val) return root;

        auto left = lowestCommonAncestor(root->left, p, q); //在左边找
        auto right = lowestCommonAncestor(root->right, p, q); //在右边找

        if (!left) return right;
        if (!right) return left;

        return root;

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
