/** https://leetcode.com/problems/linked-list-in-binary-tree
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
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
public:

    bool search(ListNode * head, TreeNode *root) {
        if(head == NULL && root == NULL) return true;
        if(head == NULL || root == NULL) return false;
        //cout << head->val << root->val << endl;
        return (head->val == root->val && (head->next == NULL ? true: search(head->next, root->left))) || (head->val == root->val &&(head->next == NULL ? true : search(head->next, root->right)));
    }
    bool isSubPath(ListNode* head, TreeNode* root) {
        if(root == NULL && head == NULL) return true;
         if(head == NULL || root == NULL) return false;
        if(search(head, root)) return true;
        bool pl = isSubPath(head, root->left);
        bool pr = isSubPath(head, root->right);
        return pl || pr;
    }
};
