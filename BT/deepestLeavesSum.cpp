//https://leetcode.com/problems/deepest-leaves-sum/submissions/
/*
Approach:
We use level-order traversal (BFS) to process the tree level by level.

The queue stores nodes of the current and upcoming levels. A NULL marker is used
to identify the end of one level.

For every node in the current level, we add its value to result.

When we encounter NULL, it means the current level has ended.

At that point:
1. If the queue is empty, it means there is no next level.
   So the current level is the deepest level, and result contains the sum of
   the deepest leaves. We return result.

2. If the queue is not empty, it means another level exists.
   So we reset result to 0 and start calculating the sum of the next level.
   We also push another NULL marker to mark the end of that next level.

In this way, result always stores the sum of the current level only.
Older level sums are discarded whenever we move to the next level.

Finally, when the last level is reached, there is no next level after it,
so the current result is returned as the answer.

Time Complexity: O(N)
We visit every node exactly once.

Space Complexity: O(W)
The queue stores nodes level by level, where W is the maximum width of the tree.
*/

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
