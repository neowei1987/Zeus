
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 
 
 /******************链表*****************/

class Solution {
public:

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL) {
            return l2;
        }
        else if (l2 == NULL) {
            return l1;
        }

        if (l1->val <= l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

    ListNode* getKthFromEnd(ListNode* head, int k) {
        if (k <= 0 || !head) {
            return NULL;
        }

        ListNode* fast= head;
        //循环何以继续？ 有下一个，或者往前走了k步
        while (k >= 1 && fast) {
            fast = fast->next;
            k--;
        }

        if (k == 0 && fast == NULL) { //节点个数正好k个
            return head;
        }
        else if (fast == NULL){   //不足k个
            throw new exception;
        }

        ListNode* slow = head;
        //循环何以继续？快指针到底（慢指针指向的便是倒数第k个节点）
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        return slow;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        //方法1: 长度差delta， 长的先走delta步， 然后遍历，比较是否一致，如果一致，则get it
        //压栈
    }

    Node* copyRandomList(Node* head) {
        return NULL;
    }

     ListNode* deleteDuplicatesLeftOne(ListNode* head) {
        ListNode* tail = head;
        ListNode* cur = head;
        while (cur && cur->next) {
            while (cur->next && cur->val == cur->next->val) {
                cur = cur->next;
            }
            tail->next = cur->next;
            tail = tail->next;
            cur = cur->next;
        }
        return head;
    }

     ListNode* deleteAllDuplicates(ListNode* head) {
        //利用哑节点，大幅减少程序复杂度
        ListNode* dummy = new ListNode(-1); 
        dummy->next = head;
        ListNode* cur = head;
        ListNode* pre = dummy;
        while (cur && cur->next) {
            if (cur->val == cur->next->val) { //相等
                while (cur->next && cur->val == cur->next->val) {
                    cur = cur->next;
                }
                pre->next = cur->next;
                cur = cur->next;
            }
            else { //不等
                pre = cur;
                cur = cur->next;
            }
        }

        return dummy->next; 
    }

    //反转整个链表；递归版
    //反转前N个节点
    //反转m～n的节点
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
