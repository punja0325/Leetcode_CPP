/*
 * @lc app=leetcode id=105 lang=cpp
 *
 * [105] Construct Binary Tree from Preorder and Inorder Traversal
 *
 * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
 *
 * algorithms
 * Medium (65.82%)
 * Likes:    15568
 * Dislikes: 553
 * Total Accepted:    1.5M
 * Total Submissions: 2.2M
 * Testcase Example:  '[3,9,20,15,7]\n[9,3,15,20,7]'
 *
 * Given two integer arrays preorder and inorder where preorder is the preorder
 * traversal of a binary tree and inorder is the inorder traversal of the same
 * tree, construct and return the binary tree.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 * Output: [3,9,20,null,null,15,7]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: preorder = [-1], inorder = [-1]
 * Output: [-1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= preorder.length <= 3000
 * inorder.length == preorder.length
 * -3000 <= preorder[i], inorder[i] <= 3000
 * preorder and inorder consist of unique values.
 * Each value of inorder also appears in preorder.
 * preorder is guaranteed to be the preorder traversal of the tree.
 * inorder is guaranteed to be the inorder traversal of the tree.
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTreehelper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
private:

    TreeNode* buildTreehelper(const vector<int>& preorder, int preorder_start, int preorder_end, 
                              const vector<int>& inorder, int inorder_start, int inorder_end) {
        
        //Boundary condition
        //If the start index is greater than the end index for either the preorder or the inorder array,
        //then we must have exhausted all the elements in the array, so we return NULL.

        if (preorder_start > preorder_end || inorder_start > inorder_end) {
            return NULL;
        }

        //Get the root value from the preorder array
        int root_val = preorder[preorder_start];
        TreeNode* root = new TreeNode(root_val);

        //Find the index of the root value in the inorder array
        //This index will be used to split the inorder array into left and right subtrees
        int inorder_root_index = 0;
        for (int i = inorder_start; i <= inorder_end; i++) {
            if (inorder[i] == root_val) {
                inorder_root_index = i;
                break;
            }
        }

        //Calculate the start and end indices for the left subtree in both the preorder and inorder arrays
        int left_preorder_start = preorder_start + 1;
        int left_preorder_end = preorder_start + inorder_root_index - inorder_start;
        int left_inorder_start = inorder_start;
        int left_inorder_end = inorder_root_index - 1;

        //Calculate the start and end indices for the right subtree in both the preorder and inorder arrays
        int right_preorder_start = preorder_start + inorder_root_index - inorder_start + 1;
        int right_preorder_end = preorder_end;
        int right_inorder_start = inorder_root_index + 1;
        int right_inorder_end = inorder_end;

        //Recursively call the buildTreehelper function for the left subtree
        root->left = buildTreehelper(preorder, left_preorder_start, left_preorder_end, inorder, left_inorder_start, left_inorder_end);

        //Recursively call the buildTreehelper function for the right subtree
        root->right = buildTreehelper(preorder, right_preorder_start, right_preorder_end, inorder, right_inorder_start, right_inorder_end);

        //Return the root of the tree
        return root;
    }
};
// @lc code=end

