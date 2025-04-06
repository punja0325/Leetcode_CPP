/*
 * @lc app=leetcode id=82 lang=cpp
 *
 * [82] Remove Duplicates from Sorted List II
 *
 * https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
 *
 * algorithms
 * Medium (47.40%)
 * Likes:    9170
 * Dislikes: 261
 * Total Accepted:    890.5K
 * Total Submissions: 1.8M
 * Testcase Example:  '[1,2,3,3,4,4,5]'
 *
 * Given the head of a sorted linked list, delete all nodes that have duplicate
 * numbers, leaving only distinct numbers from the original list. Return the
 * linked list sorted as well.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,3,4,4,5]
 * Output: [1,2,5]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,1,1,2,3]
 * Output: [2,3]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is in the range [0, 300].
 * -100 <= Node.val <= 100
 * The list is guaranteed to be sorted in ascending order.
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
class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (!head)
            return head;
        ListNode dummy(0, head);
        ListNode *prev = NULL;
        ListNode *curr = head;
        ListNode *next;
        ListNode *write_ptr = &dummy;
        while (curr)
        {
            next = curr->next;
            bool isDuplicate = true;
            if (!prev && !next)
            {
                isDuplicate = false;
            }
            else if (prev == NULL)
            {
                if (next && next->val != curr->val)
                    isDuplicate = false;
            }
            else if (next == NULL)
            {
                if (prev && prev->val != curr->val)
                    isDuplicate = false;
            }
            else
            {
                if (prev->val != curr->val && curr->val != next->val)
                    isDuplicate = false;
            }
            if (!isDuplicate)
            {
                write_ptr->next = curr;
                write_ptr = write_ptr->next;
            }
            // Go to the next check point
            prev = curr;
            curr = curr->next;
        }
        write_ptr->next = NULL;
        return dummy.next;
    }
};

// @lc code=end

