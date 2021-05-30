// https://leetcode.com/problems/palindrome-partitioning-ii/
class Solution {
public:
    bool isPalindrome(string s) {
        //cout << s << endl;
        int end = s.length()-1, start = 0;
        while(start <= end) {
            if(s[start++] != s[end--]) return false;
        }
        return true;
    }
    int minCut(string s) {
        int n = s.length();
        vector<vector<bool>> isPalin(n, vector<bool>(n,false));
        
        vector<int> in(s.length(),0);
        for(int i = 0 ; i < n; i++) isPalin[i][i] = true;
        for(int i = 0;  i < n-1; i++) isPalin[i][i+1] = s[i] == s[i+1];
        for(int diff = 2; diff < n; diff++) {
            for(int i = 0; i + diff < n; i++) {
                int j = i+diff;
                if(s[i] == s[j] ) isPalin[i][j] = isPalin[i+1][j-1];
            }
        }
        for(int i = 0; i < n; i++) in[i]= i;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(isPalin[0][i]) in[i] = 0;
                //cout <<i << j << in[i] << in[j] << endl;
              else if(isPalin[j+1][i]) {
                  in[i] = min(in[i], in[j]+1);
              }  
            }
        }
        return in[n-1];
    }
};
