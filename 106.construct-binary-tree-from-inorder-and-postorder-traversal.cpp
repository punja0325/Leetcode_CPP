/*
 * @lc app=leetcode id=106 lang=cpp
 *
 * [106] Construct Binary Tree from Inorder and Postorder Traversal
 *
 * https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/
 *
 * algorithms
 * Medium (65.30%)
 * Likes:    8343
 * Dislikes: 141
 * Total Accepted:    783.8K
 * Total Submissions: 1.2M
 * Testcase Example:  '[9,3,15,20,7]\n[9,15,7,20,3]'
 *
 * Given two integer arrays inorder and postorder where inorder is the inorder
 * traversal of a binary tree and postorder is the postorder traversal of the
 * same tree, construct and return the binary tree.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
 * Output: [3,9,20,null,null,15,7]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: inorder = [-1], postorder = [-1]
 * Output: [-1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= inorder.length <= 3000
 * postorder.length == inorder.length
 * -3000 <= inorder[i], postorder[i] <= 3000
 * inorder and postorder consist of unique values.
 * Each value of postorder also appears in inorder.
 * inorder is guaranteed to be the inorder traversal of the tree.
 * postorder is guaranteed to be the postorder traversal of the tree.
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        //inorder: left, root, right
        //postorder: left, right, root
        return buildTreehelper(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
private:
    TreeNode* buildTreehelper(vector<int>& inorder, int inorder_start, int inorder_end, vector<int>& postorder, int postorder_start, int postorder_end) {
        if (inorder_start > inorder_end || postorder_start > postorder_end) return NULL;
        int root_val = postorder[postorder_end];
        TreeNode* root = new TreeNode(root_val);
        //find out root_val index in inorder array
        int inorder_root_index = 0;
        for(int i = inorder_start; i <= inorder_end; i++) {
            if (inorder[i] == root_val) {
                inorder_root_index = i;
                break;
            }
        }
        //inorder: left, root, right
        //postorder: left, right, root
        int left_inorder_start = inorder_start;
        int left_inorder_end = inorder_root_index - 1;
        int left_postorder_start = postorder_start;
        int left_postorder_end = postorder_start + inorder_root_index - left_inorder_start - 1;

        int right_inorder_start = inorder_root_index + 1;
        int right_inorder_end = inorder_end;
        int right_postorder_start = left_postorder_end + 1;
        int right_postorder_end = postorder_end - 1;
        root->left = buildTreehelper(inorder, left_inorder_start, left_inorder_end, postorder, left_postorder_start, left_postorder_end);
        root->right = buildTreehelper(inorder, right_inorder_start, right_inorder_end, postorder, right_postorder_start, right_postorder_end);
        return root;

    }
};
// @lc code=end

