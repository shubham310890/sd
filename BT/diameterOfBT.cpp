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
    int diameter(TreeNode * root, int & max) {
        if(root == NULL) { 
            return 0;
                         }
        if(root->left == NULL && root->right == NULL) return 1;
        int ld = diameter(root->left, max);
        int rd = diameter(root->right, max);
        max = (ld+rd+1 > max) ? ld+rd+1 : max;
        return (ld > rd ? ld : rd) + 1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if(root == NULL) return 0;
        int max = 0;
        diameter(root, max);
        return max > 0 ? max-1 : 0;
    }
};
