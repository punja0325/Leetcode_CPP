/*
 * @lc app=leetcode id=226 lang=cpp
 *
 * [226] Invert Binary Tree
 *
 * https://leetcode.com/problems/invert-binary-tree/description/
 *
 * algorithms
 * Easy (78.40%)
 * Likes:    14372
 * Dislikes: 236
 * Total Accepted:    2.4M
 * Total Submissions: 3.1M
 * Testcase Example:  '[4,2,7,1,3,6,9]'
 *
 * Given the root of a binary tree, invert the tree, and return its root.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [4,2,7,1,3,6,9]
 * Output: [4,7,2,9,6,3,1]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [2,1,3]
 * Output: [2,3,1]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = []
 * Output: []
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [0, 100].
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

//#define BFS //Queue
//#define DFS_RECURSIVE
#define DFS_ITERATIVE //Stack
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        #ifdef DFS_ITERATIVE
        if (!root) return NULL; // Base case: if the node is NULL, return NULL
        stack<TreeNode*> s;
        s.push(root);
        while(!s.empty()) {
            TreeNode* node = s.top(); s.pop();// Get the top node (last-in)

            // Swap the left and right child nodes
            swap(node->left, node->right);
            // Push children into the stack
            // Note: Push right first, then left to process left first (mimicking recursive DFS)
            if (node->right) s.push(node->right);
            if (node->left) s.push(node->left);
        }
        return root;
        #endif
        #ifdef DFS_RECURSIVE
        if (!root) return NULL; // Base case: if the node is NULL, return NULL
        // Recursively invert left and right subtrees
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        // Swap the left and right children
        root->left = right;
        root->right = left;
        return root;

        #endif
        #ifdef BFS
        //BPS
        if (!root) return NULL;//if tree is empty, return NULL
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            if (node) {
                TreeNode* temp = node->left;
                node->left = node->right;
                node->right = temp;
                //swap(node->left, node->right);
                q.push(node->left);
                q.push(node->right);

            }
        }
        return root;
        #endif
    }
};
// @lc code=end

