/*
 * @lc app=leetcode id=104 lang=cpp
 *
 * [104] Maximum Depth of Binary Tree
 *
 * https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
 *
 * algorithms
 * Easy (76.60%)
 * Likes:    13275
 * Dislikes: 250
 * Total Accepted:    3.7M
 * Total Submissions: 4.8M
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given the root of a binary tree, return its maximum depth.
 *
 * A binary tree's maximum depth is the number of nodes along the longest path
 * from the root node down to the farthest leaf node.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [3,9,20,null,null,15,7]
 * Output: 3
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,null,2]
 * Output: 2
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [0, 10^4].
 * -100 <= Node.val <= 100
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

    int maxDepth(TreeNode* root) {
        #if 0
        //Interative (BFS(Breadth-First Search) + Queue)
        if (!root) return 0;//Base case: empty tree has depth 0
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int levelSize = q.size();//Number of the nodes at the current level
            depth++;

            //Process all nodes at the current queue
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                q.pop();
            }
        }
        return depth;
        #else
        if (root == 0) {
            return 0;
        }
        int max_left_depth = 1 + maxDepth(root->left);
        int max_right_depth = 1 + maxDepth(root->right);
        return max(max_left_depth, max_right_depth);
        #endif
    }
};
// @lc code=end

