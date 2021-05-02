/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Codec {

    String sHelper(TreeNode root, String st)
    {
        if(root == null) 
        {
            st += "N,";
            return st;
        }
        st = st + root.val + ",";
        st = sHelper(root.left, st);
        st = sHelper(root.right, st);
        return st;
    }
    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        String st = "";
        st = sHelper(root,st);
        //System.out.println(st);
        return st;
    }
    TreeNode dHelper(List<String> list)
    {
        if(list.get(0).equals("N"))
        {
            list.remove(0);
            return null;
        }
        TreeNode root = new TreeNode(Integer.parseInt(list.get(0)));
        list.remove(0);
        root.left = dHelper(list);
        root.right = dHelper(list);
        return root;
    }
    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        String[] st = data.split(",");
        List<String> data_list = new LinkedList<String>(Arrays.asList(st));
        return dHelper(data_list);
    }
}
