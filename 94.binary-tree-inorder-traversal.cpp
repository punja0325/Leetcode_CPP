/*
 * @lc app=leetcode id=94 lang=cpp
 *
 * [94] Binary Tree Inorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-inorder-traversal/description/
 *
 * algorithms
 * Easy (77.77%)
 * Likes:    13868
 * Dislikes: 824
 * Total Accepted:    2.9M
 * Total Submissions: 3.8M
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given the root of a binary tree, return the inorder traversal of its nodes'
 * values.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [1,null,2,3]
 *
 * Output: [1,3,2]
 *
 * Explanation:
 *
 *
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
 *
 * Output: [4,2,6,5,7,1,3,9,8]
 *
 * Explanation:
 *
 *
 *
 *
 * Example 3:
 *
 *
 * Input: root = []
 *
 * Output: []
 *
 *
 * Example 4:
 *
 *
 * Input: root = [1]
 *
 * Output: [1]
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
 *
 * Follow up: Recursive solution is trivial, could you do it iteratively?
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

//#define RECURSIVE
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        //inorder: left > root(node) > right
        //[1, null, 2, 3] > [1, 3, 2]
#ifdef RECURSIVE
        vector<int> res; // Vector to store the traversal result
        inorderhelper(root, res); // Call the helper function to perform traversal
        return res;
#else
        // Iterative solution using a stack
        if (!root) return {}; // If the tree is empty, return an empty vector
        vector<int> res;      // Vector to store the traversal result
        stack<TreeNode*> s;   // Stack to simulate the recursion call stack
        TreeNode* cur = root; // Pointer to the current node
        while (cur || !s.empty()) {
            // Traverse to the leftmost node
            while (cur) {
                s.push(cur); // Push the current node onto the stack
                cur = cur->left; // Move to the left child
            }
            // Current node is null, pop a node from the stack
            cur = s.top();
            s.pop();
            res.push_back(cur->val);// Add the node's value to the result
            cur = cur->right; // Move to the right child
        }
        return res;
#endif
    }
#ifdef RECURSIVE
private:
    void inorderhelper(TreeNode* root, vector<int>& res) {
        if (!root) return; // Base case: if the node is null, return
        inorderhelper(root->left, res); // Recursively traverse the left subtree
        res.push_back(root->val);       // Add the current node's value to the result
        inorderhelper(root->right, res);// Recursively traverse the right subtree
    }
#endif
};
// @lc code=end

