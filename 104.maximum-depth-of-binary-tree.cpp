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
    #if 1
    public:
        int maxDepth(TreeNode* root) {
            //DFS
            if (!root) return 0;
            stack<pair<TreeNode*, int>> st;
            st.push({root, 1});
            int maxDepth = 0;
            while(!st.empty()) {
                auto [node, depth] = st.top(); st.pop();
                if (node) {
                    maxDepth = max(depth, maxDepth);
                    if (node->left) st.push({node->left, depth+1});
                    if (node->right) st.push({node->right, depth+1});
                }
            }
            return maxDepth;
        }
    #elif 1
    public:
        int maxDepth(TreeNode* root) {
            //BFS
            if (!root) return 0;
            queue<TreeNode*> q;
            q.push(root);
            int depth = 0;
            while(!q.empty()) {
                int levelSize = q.size(); // Number of the nodes in the current level
                depth++;
                for(int i = 0; i < levelSize; i++) {
                    TreeNode* node = q.front(); q.pop();
                    if (node->left) q.push(node->left);
                    if (node->right) q.push(node->right);
                }
            }
            return depth;
        }
    #else
    public:
        int maxDepth(TreeNode* root) {
            if (root == NULL) return 0;
            int leftDepth = maxDepth(root->left);
            int rightDepth = maxDepth(root->right);
            return max(leftDepth, rightDepth) + 1;
        }
    #endif
    };
// @lc code=end

