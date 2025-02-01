/*
 * @lc app=leetcode id=144 lang=cpp
 *
 * [144] Binary Tree Preorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-preorder-traversal/description/
 *
 * algorithms
 * Easy (71.93%)
 * Likes:    8239
 * Dislikes: 215
 * Total Accepted:    1.9M
 * Total Submissions: 2.6M
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given the root of a binary tree, return the preorder traversal of its nodes'
 * values.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,null,2,3]
 * 
 * Output: [1,2,3]
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
 * Output: [1,2,4,5,6,7,3,8,9]
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
//#define RECURSIVE_SOLUTION
#define STACK_SOLUTION
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        #ifdef STACK_SOLUTION
        if (!root) return {}; //If the tree is empty, return an empty vector
        vector<int> res; //Vector to store the traveral result
        stack<TreeNode*> s; // Stack to simulate the recursive result
        s.push(root);  // Push the root node onto the stack

        while (!s.empty()) {
            TreeNode* node = s.top();
            s.pop();
            res.push_back(node->val);
            if (node->right) s.push(node->right);
            if (node->left) s.push(node->left);
        }
        return res;

        #endif
        #ifdef RECURSIVE_SOLUTION
        vector<int> res;
        preorderhelper(root, res);
        return res;
        #endif
        
    }
#ifdef RECURSIVE_SOLUTION
private:
    void preorderhelper(TreeNode* root, vector<int>& res) {
        if (!root) return; //Base case: if the node is null, return
        res.push_back(root->val);
        preorderhelper(root->left, res);
        preorderhelper(root->right, res);
    }
#endif
};
// @lc code=end

