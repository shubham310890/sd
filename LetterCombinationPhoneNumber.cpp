//https://leetcode.com/problems/letter-combinations-of-a-phone-number/
class Solution {
public:
    string in[10] = {"0","1","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    void helper(string digits, vector<string> & result, int index)
    {
        if(digits.length() == 0) return;
        queue<string> q;
        q.push("");
        while(!q.empty())
        {
            string f = q.front();
            q.pop();
            if(f.length() == digits.length()) {
                result.push_back(f);
            }
           else {
            for(auto letter : in[digits[f.length()]-'0'])
            {
                q.push(f+letter);
            }
               }
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        helper(digits, result, 0);
        return result;
    }
};
