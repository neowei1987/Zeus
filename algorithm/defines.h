
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
using namespace std; 

std::ostream& operator << (std::ostream& in, std::vector<int>& target);
std::istream& operator >> (std::istream& in, std::vector<int>& target);

typedef std::pair<int, int> PII;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
