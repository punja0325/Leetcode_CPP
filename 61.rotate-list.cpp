/*
 * @lc app=leetcode id=61 lang=cpp
 *
 * [61] Rotate List
 *
 * https://leetcode.com/problems/rotate-list/description/
 *
 * algorithms
 * Medium (37.68%)
 * Likes:    10307
 * Dislikes: 1494
 * Total Accepted:    1.2M
 * Total Submissions: 3.1M
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * Given the head of a linked list, rotate the list to the right by k
 * places.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [4,5,1,2,3]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [0,1,2], k = 4
 * Output: [2,0,1]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is in the range [0, 500].
 * -100 <= Node.val <= 100
 * 0 <= k <= 2 * 10^9
 *
 *
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
class Solution {
    public:
        ListNode* rotateRight(ListNode* head, int k) {
            // Edge case: If the list is empty or has only one element, no rotation is needed.
            if (!head || !head->next) return head;

            // Step 1: Find the length of the list and the last node.
            ListNode* current = head;
            int length = 1;  // The length of the list.

            while (current->next) {
                current = current->next;
                length++;
            }

            // Step 2: Make the list circular (connect the last node to the head).
            current->next = head;

            // Step 3: Calculate the effective number of rotations.
            k = k % length;  // Avoid unnecessary rotations (e.g., when k >= length)

            // Step 4: Find the new tail, which is at (length - k % length - 1).
            ListNode* newTail = head;
            for (int i = 0; i < length - k - 1; i++) {
                newTail = newTail->next;
            }

            // Step 5: The new head is the node after the new tail.
            ListNode* newHead = newTail->next;

            // Step 6: Break the circular list.
            newTail->next = nullptr;

            return newHead;
        }
    };

// @lc code=end

