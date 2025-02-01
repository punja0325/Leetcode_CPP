// 结构体定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/*
        1
       / \
      2   3
     / \   \
    4   5   6
Pre-order 遍历：1 -> 2 -> 4 -> 5 -> 3 -> 6
In-order 遍历：4 -> 2 -> 5 -> 1 -> 3 -> 6
Post-order 遍历：4 -> 5 -> 2 -> 6 -> 3 -> 1
*/

// 递归实现树的遍历
void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    std::cout << root->val << " "; // 访问根节点
    preorderTraversal(root->left); // 递归访问左子树
    preorderTraversal(root->right); // 递归访问右子树
}

void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left); // 递归访问左子树
    std::cout << root->val << " "; // 访问根节点
    inorderTraversal(root->right); // 递归访问右子树
}

void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left); // 递归访问左子树
    postorderTraversal(root->right); // 递归访问右子树
    std::cout << root->val << " "; // 访问根节点
}

////////////
// 迭代实现树的遍历
void preorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stack;
    while (root != NULL || !stack.empty()) {
        while (root != NULL) {
            std::cout << root->val << " "; // 访问根节点
            stack.push(root);
            root = root->left; // 移动到左子树
        }
        root = stack.top();
        stack.pop();
        root = root->right; // 移动到右子树
    }
}

void inorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stack;
    while (root != NULL || !stack.empty()) {
        while (root != NULL) {
            stack.push(root);
            root = root->left; // 移动到左子树
        }
        root = stack.top();
        stack.pop();
        std::cout << root->val << " "; // 访问根节点
        root = root->right; // 移动到右子树
    }
}

void postorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stack;
    std::stack<TreeNode*> output;
    while (root != NULL || !stack.empty()) {
        while (root != NULL) {
            output.push(root);
            stack.push(root);
            root = root->right; // 移动到右子树
        }
        root = stack.top();
        stack.pop();
        root = root->left; // 移动到左子树
    }
    while (!output.empty()) {
        std::cout << output.top()->val << " "; // 访问根节点
        output.pop();
    }
}