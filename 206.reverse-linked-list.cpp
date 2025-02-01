/*
 * @lc app=leetcode id=206 lang=cpp
 *
 * [206] Reverse Linked List
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#define METHOD_STACK
#define METHOD_THREE_POINTERS
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        #if 1
        ListNode* prev = NULL;
        ListNode* cur = head;
        ListNode* next;
        while(cur != NULL) {
            next = cur->next; //Store the next node
            cur->next = prev; // Reverse the current node's pointer
            prev = cur; // Move prev and cur one step forward
            cur = next;
        }
        return prev;
        #else
        if (head == NULL) return head;
        stack<ListNode*> s;
        //push into stach and then pop
        ListNode *cur = head;
        //push into stach
        while (cur != NULL) {
            s.push(cur);
            cur = cur->next;
        }
        head = s.top();
        cur = head;
        s.pop();
        //pop
        while (!s.empty()) {
            cur->next = s.top();
            cur = cur->next;
            s.pop();
        }
        cur->next = NULL;
        #endif  
        return head;
    }
};
// @lc code=end

