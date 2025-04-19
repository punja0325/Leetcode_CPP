/*
 * @lc app=leetcode id=222 lang=cpp
 *
 * [222] Count Complete Tree Nodes
 *
 * https://leetcode.com/problems/count-complete-tree-nodes/description/
 *
 * algorithms
 * Easy (68.53%)
 * Likes:    9024
 * Dislikes: 564
 * Total Accepted:    934.9K
 * Total Submissions: 1.3M
 * Testcase Example:  '[1,2,3,4,5,6]'
 *
 * Given the root of a complete binary tree, return the number of the nodes in
 * the tree.
 * 
 * According to Wikipedia, every level, except possibly the last, is completely
 * filled in a complete binary tree, and all nodes in the last level are as far
 * left as possible. It can have between 1 and 2^h nodes inclusive at the last
 * level h.
 * 
 * Design an algorithm that runs in less than O(n) time complexity.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2,3,4,5,6]
 * Output: 6
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = []
 * Output: 0
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = [1]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [0, 5 * 10^4].
 * 0 <= Node.val <= 5 * 10^4
 * The tree is guaranteed to be complete.
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
#if 0
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int count = 0;
        
        while(!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            count++;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        return count;
    }
};
#else
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;

        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        if (leftHeight == rightHeight) {
            // 左子樹是滿的，節點數是 2^leftHeight - 1，加上 root 和右子樹
            return (1 << leftHeight) + countNodes(root->right);
        } else {
            // 右子樹是滿的，節點數是 2^rightHeight - 1，加上 root 和左子樹
            return (1 << rightHeight) + countNodes(root->left);
        }
    }

private:
    int getHeight(TreeNode* node) {
        int height = 0;
        while (node) {
            node = node->left;
            height++;
        }
        return height;
    }
};

#endif
// @lc code=end

