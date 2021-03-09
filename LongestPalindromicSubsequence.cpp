/*
https://leetcode.com/problems/longest-palindromic-subsequence
*/
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int result = 1;
        vector<vector<int>> lcs(s.length());
        for(int i = 0; i < s.length(); i++)
        {
            for(int j = 0; j < s.length(); j++)
            {
                lcs[i].push_back(1);
            }
        }
        for(int i = 0 ; i < s.length()-1; i++)
        {
            lcs[i][i+1] = s[i] == s[i+1] ? 2 : 1;
            result = lcs[i][i+1] > result ? lcs[i][i+1] : result;
        }
        for(int diff = 2; diff < s.length(); diff++)
        {
            for(int i = 0; i+diff < s.length(); i++)
            {
                int j = i+diff;
                if(s[i]==s[j])
                {
                    lcs[i][j] = lcs[i+1][j-1]+2;
                }
                else 
                {
                    lcs[i][j] = lcs[i+1][j] > lcs[i][j-1] ? lcs[i+1][j] : lcs[i][j-1];
                }
                result = lcs[i][j] > result ? lcs[i][j] : result;
            }
        }
        return result;
    }
};
