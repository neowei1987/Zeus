#include <iostream>
using namespace std;

struct TreeNode {
    TreeNode* left;
    TreeNOde* right;
    int data;
};

vector<int> rightView(TreeNode* root) {
    vector<int> res;
    if (!root) return res;
    queue<TreeNode*> q;
    
    q.push(root);
    q.push(nullptr);
    
    while (q.size()) {
        auto r = q.top();
        q.pop();
        if (r->left) q.push(r->left);
        if (r->right) q.push(r->right)；
        auto p =  q.top();
        if (p == null) {
            res.push_back(r->data);
            q.pop();
            if (q.empty()) {
                break;
            }
            q.push(nullptr);
        }
    }
    
    return res;   
}
int main() {
    //int a;
    //cin >> a;
    cout << "Hello World!" << endl;
}