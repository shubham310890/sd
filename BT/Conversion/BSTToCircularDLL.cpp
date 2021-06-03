//https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/
class Solution {
public:
    void treeToDLLHelper(Node * root, Node * & head, Node * & prev)
    {
        if(root == NULL) return;
        treeToDLLHelper(root->left, head, prev);
        if(head == NULL) {
            head = root;
        } else {
            prev->right = root;
            root->left = prev;
        }
        prev = root;
        //cout << prev << endl;
        treeToDLLHelper(root->right, head, prev);
    }
    Node* treeToDoublyList(Node* root) {
        Node * head = NULL, *prev = NULL;
        treeToDLLHelper(root, head, prev);
        if(head) {
        head->left = prev;
        prev->right = head;
        }
        return head;
    }
};
