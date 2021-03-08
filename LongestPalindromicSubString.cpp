/*
https://leetcode.com/problems/longest-palindromic-substring
https://leetcode.com/submissions/detail/465195906/
*/
class Solution {
public:
    string longestPalindrome(string s) {
        vector<vector<bool>> isPalin(s.length());
        int start_id = -1, end_id = -1;
        for(int i = 0 ; i < s.length() ; i++)
        {
            for(int j = 0; j < s.length(); j++)
            {
                isPalin[i].push_back(false);
            }
        }
        for(int i = 0 ; i < s.length() ; i++)
        {
            isPalin[i][i] = true;
        }
        for(int i = 0 ; i < s.length()-1; i++)
        {
            isPalin[i][i+1] = s[i] == s[i+1] ? true : false;
            if(isPalin[i][i+1])
            {
                start_id = i;
                end_id = i+1;
            }
        }
        for(int diff = 2; diff < s.length(); diff++)
        {
            for(int i = 0; i + diff < s.length(); i++)
            {
                int j = i+diff;
                if(s[i] == s[j])
                {
                    isPalin[i][j] = isPalin[i+1][j-1];
                    if(isPalin[i][j]  && j-i > end_id-start_id)
                    {
                        start_id = i;
                        end_id = j;
                    }
                }
                else {
                    isPalin[i][j] = false;
                }
            }
        }
        if(start_id != -1)
        {
            string result = s.substr(start_id, end_id-start_id+1);
            return result;
        }
        else
        {
           return s.substr(0,1);
        }
    }
};
