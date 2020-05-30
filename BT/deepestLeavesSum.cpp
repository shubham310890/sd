//https://leetcode.com/problems/deepest-leaves-sum/submissions/
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
    struct Node {
        struct TreeNode * node;
        int level;
    };
    typedef struct Node Node;
public:
    int getMaxLevel(TreeNode *root) {
        if(root == NULL) return 0;
        queue<TreeNode*> q;
        q.push(root);
        q.push(NULL);
        int result = 0;
        while(q.empty() == false) {
            TreeNode * top = q.front();
            q.pop();
            result += top != NULL ? top->val : 0;
            if(top == NULL) {
                if(q.empty()) return result;
                result = 0;
                q.push(NULL);
            } else {
                if(top->left != NULL) {
                    q.push(top->left);
                }
                if(top->right != NULL) {
                    q.push(top->right);
                }
            }
        }
        return 0;
    }
    
    int deepestLeavesSum(TreeNode* root) {
        return getMaxLevel(root);
    }
};
