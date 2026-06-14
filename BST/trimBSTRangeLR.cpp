// https://leetcode.com/problems/trim-a-binary-search-tree
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
     /* one more solution
     */
     TreeNode* trimBSTHelper(TreeNode* root, int low, int high) {
        if (root == NULL) return NULL;
        if(root->left == NULL && root->right == NULL) {
            if(root->val < low || root->val > high) return NULL;
            else root;
        }
        root->left = trimBSTHelper(root->left, low, high);
        root->right = trimBSTHelper(root->right, low, high);
        if (root->val < low) return root->right;
        else if (root->val > high) return root->left;
        else return root;
    }
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == NULL) return NULL;
        return trimBSTHelper(root, low, high);
    }
  
     TreeNode* trimBST(TreeNode* root, int L, int R) {
        if(root == NULL) return NULL;
        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        if(root->val < L || root->val > R) {
            if(root->left != NULL) {
                TreeNode * temp = root->left->right;
                if(root->right == NULL) {
                    root->right = root->left->right;
                } else {
                    TreeNode * minNode = root->right;
                    while(minNode->left != NULL){
                        minNode = minNode->left;
                    }
                    minNode->left = root->left->right;
                }
                TreeNode * result = root->left;
                //delete(root);
                root->left=NULL;
                return result;
            } else if(root->right != NULL) {
                TreeNode * result = root->right;
                //delete(root);
                root->right=NULL;
                return result;
            } else { 
            return NULL;
            }
        }
         return root;
    }
};
