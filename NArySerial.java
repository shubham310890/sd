/*
// Definition for a Node.
class Node {
    public int val;
    public List<Node> children;

    public Node() {}

    public Node(int _val) {
        val = _val;
    }

    public Node(int _val, List<Node> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Codec {
    String sHelper(Node root, String st)
    {
        if(root==null)
        {
            return "N,";
        }
        st = st + root.val + ":" + root.children.size()+",";
        for(int i = 0; i < root.children.size(); i++)
        {
            st = sHelper(root.children.get(i),st);
        }
        return st;
    }
    // Encodes a tree to a single string.
    public String serialize(Node root) {
        String st = "";
        st = sHelper(root,"");
        //System.out.println(st);
        return st;
    }
	
    Node dHelper(List<String> list)
    {
        if(list.get(0).equals("N"))
        {
            list.remove(0);
            return null;
        }
        String st= list.get(0);
        String[] st1 = st.split(":");
        List<Node> childs = new ArrayList<Node>();
        Node root = new Node(Integer.parseInt(st1[0]), childs);
        list.remove(0);
        if(st1[1].equals("0") == false)
        {
            for(int i = 0; i < Integer.parseInt(st1[1]); i++)
            {
                root.children.add(i, dHelper(list));
            }
        }
        return root;
    }
    // Decodes your encoded data to tree.
    public Node deserialize(String data) {
        String[] st = data.split(",");
        List<String> data_list = new LinkedList<String>(Arrays.asList(st));
        return dHelper(data_list);
    }
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.deserialize(codec.serialize(root));
