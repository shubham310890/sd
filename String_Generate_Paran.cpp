class Solution {
public:
    void helper(vector<string>& out, string st, int open_count, int closed_count, int n, map<string, bool> & m)
    {
        if(st.length() == 2*n && m.find(st) == m.end())
        {
            out.push_back(st);
            m[st] = true;
            return;
        }
        if(open_count > 0) {
            helper(out, st+"(", open_count-1, closed_count, n, m);
            if(closed_count > 0)
            helper(out, st+"()", open_count-1, closed_count-1, n, m);
        } 
        if(closed_count > 0 && closed_count > open_count)
        {
            helper(out, st+")", open_count, closed_count-1, n, m);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        map<string, bool> m;
        string st = "";
        helper(result, st, n, n, n, m);
        return result;
    }
};
