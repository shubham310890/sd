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

    private int diameter = 0;

    public int diameterOfBinaryTree(TreeNode root) {
        height(root);
        return diameter;
    }

    private int height(TreeNode node) {
        if (node == null) {
            return 0;
        }

        int leftHeight = height(node.left);
        int rightHeight = height(node.right);

        // Diameter passing through current node
        int currentDiameter = leftHeight + rightHeight;

        diameter = Math.max(diameter, currentDiameter);

        // Height of current node
        return 1 + Math.max(leftHeight, rightHeight);
    }
}

import java.util.*;

class Solution {

    private List<TreeNode> diameterPath = new ArrayList<>();

    public List<TreeNode> diameterNodes(TreeNode root) {
        dfs(root);
        return diameterPath;
    }

    private DownInfo dfs(TreeNode node) {
        if (node == null) {
            return new DownInfo(0, new ArrayList<>());
        }

        DownInfo left = dfs(node.left);
        DownInfo right = dfs(node.right);

        // Build candidate diameter path passing through current node
        List<TreeNode> candidate = new ArrayList<>();

        // left path is from left child -> leaf
        // reverse it to make leaf -> left child
        List<TreeNode> leftPath = new ArrayList<>(left.path);
        Collections.reverse(leftPath);

        candidate.addAll(leftPath);
        candidate.add(node);
        candidate.addAll(right.path);

        // Update global diameter path if this one is better
        if (candidate.size() > diameterPath.size()) {
            diameterPath = candidate;
        }

        // Return longest downward path starting from current node
        List<TreeNode> downPath = new ArrayList<>();
        downPath.add(node);

        if (left.height >= right.height) {
            downPath.addAll(left.path);
            return new DownInfo(left.height + 1, downPath);
        } else {
            downPath.addAll(right.path);
            return new DownInfo(right.height + 1, downPath);
        }
    }

    private static class DownInfo {
        int height;              // height in number of nodes
        List<TreeNode> path;     // path from current node to deepest leaf

        DownInfo(int height, List<TreeNode> path) {
            this.height = height;
            this.path = path;
        }
    }
}

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
