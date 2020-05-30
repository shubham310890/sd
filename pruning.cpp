https://leetcode.com/problems/binary-tree-pruning
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
    bool pruneTree1(TreeNode * root) {
        if(root == NULL) return true;
        if(root->left == NULL && root->right == NULL) return root->val == 0;
        bool isLeft = pruneTree1(root->left);
        bool isRight = pruneTree1(root->right);
        if(isLeft && isRight && root->val==0) {
            return true;
        }
        root->left = isLeft ? NULL: root->left;
        root->right = isRight ? NULL: root->right;
        return false;
        
    }
    TreeNode* pruneTree(TreeNode* root) {
        bool temp = pruneTree1(root);
        if(temp) return NULL;
        return root;
    }
};
