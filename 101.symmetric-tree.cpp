/*
 * @lc app=leetcode id=101 lang=cpp
 *
 * [101] Symmetric Tree
 *
 * https://leetcode.com/problems/symmetric-tree/description/
 *
 * algorithms
 * Easy (58.35%)
 * Likes:    15776
 * Dislikes: 400
 * Total Accepted:    2.3M
 * Total Submissions: 3.9M
 * Testcase Example:  '[1,2,2,3,4,4,3]'
 *
 * Given the root of a binary tree, check whether it is a mirror of itself
 * (i.e., symmetric around its center).
 *
 *
 * Example 1:
 *
 *
 * Input: root = [1,2,2,3,4,4,3]
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,2,2,null,3,null,3]
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 1000].
 * -100 <= Node.val <= 100
 *
 *
 *
 * Follow up: Could you solve it both recursively and iteratively?
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
#define INTERATIVE_SOLUTION
/*
- Use a queue to compare nodes level by level.
- Push the left and right children of the root into the queue.
- For each pair of nodes, check if they are mirrors.
*/

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        #ifdef INTERATIVE_SOLUTION
        if (!root) return true;
        queue<pair<TreeNode*, TreeNode*>> q;
        q.push({root, root});
        while(!q.empty()) {
            int levelSize = q.size();
            for(int i = 0; i < levelSize; i++) {
                auto [node1, node2] = q.front(); q.pop();
                if (!node1 && !node2) continue;
                if (!node1 || !node2) return false;
                if(node1->val != node2->val) return false;
                q.push({node1->left, node2->right});
                q.push({node1->right, node2->left});
            }
        }
        return true;

        #endif
        #ifdef RECURSIVE_SOLUTION
        if (!root) return true; /// If the tree is empty, it is symmetric
        return isMirror(root->left, root->right); // Check if left and right subtrees are mirrors
        #endif

    }
#ifdef RECURSIVE_SOLUTION
private:
    bool isMirror(TreeNode* left, TreeNode* right) {
        // If both nodes are null, they are mirrors
        if (!left && !right) return true;
        // If one is null and the other is not, they are not mirrors
        if (!left || !right) return false;
        // Check if the current nodes' values are equal
        if (left->val != right->val) return false;
        // Recursively check the subtrees
        return isMirror(left->left, right->right) && isMirror(left->right, right->left);
    }
#endif
};
// @lc code=end

