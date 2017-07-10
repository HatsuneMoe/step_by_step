#include <iostream>

using std::cout;
using std::endl;


class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
};

class Solution {
public:
    /**
     * @param root: The root of binary tree.
     * @return: An integer
     */
    int maxDepth(TreeNode *root) {
        // write your code here
        if (root == nullptr)
            return 0;
        if (root->left == nullptr && root->right == nullptr)
            return 1;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return (left > right)? left+1: right+1;
    }
};

int main()
{
    Solution A;
    TreeNode *root;
    root = new TreeNode (1);
//    root->left = new TreeNode (2);
//    root->right = new TreeNode (3);
//    root->right->left = new TreeNode (4);
//    root->right->right = new TreeNode (5);
    std::cout << A.maxDepth(root) << std::endl;
    return 0;
}