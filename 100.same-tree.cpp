/*
 * @lc app=leetcode id=100 lang=cpp
 *
 * [100] Same Tree
 *
 * https://leetcode.com/problems/same-tree/description/
 *
 * algorithms
 * Easy (62.02%)
 * Likes:    12080
 * Dislikes: 262
 * Total Accepted:    2.7M
 * Total Submissions: 4.2M
 * Testcase Example:  '[1,2,3]\n[1,2,3]'
 *
 * Given the roots of two binary trees p and q, write a function to check if
 * they are the same or not.
 *
 * Two binary trees are considered the same if they are structurally identical,
 * and the nodes have the same value.
 *
 *
 * Example 1:
 *
 *
 * Input: p = [1,2,3], q = [1,2,3]
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: p = [1,2], q = [1,null,2]
 * Output: false
 *
 *
 * Example 3:
 *
 *
 * Input: p = [1,2,1], q = [1,1,2]
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in both trees is in the range [0, 100].
 * -10^4 <= Node.val <= 10^4
 *
 *
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<pair<TreeNode*, TreeNode*>> que;
        que.push({p, q});
        while(!que.empty()) {
            int levelCount = que.size();
            for(int i = 0; i < levelCount; i++) {
                auto [p_node, q_node] = que.front(); que.pop();
                if (p_node && q_node) {
                    if (p_node->val != q_node->val) {
                        return false;
                    }
                    TreeNode* p_left = p_node->left;
                    TreeNode* p_right = p_node->right;
                    TreeNode* q_left = q_node->left;
                    TreeNode* q_right = q_node->right;
                    que.push({p_left, q_left});
                    que.push({p_right, q_right});
                } else if (!p_node && !q_node) {
                    continue;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};
// @lc code=end

