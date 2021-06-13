// https://leetcode.com/explore/interview/card/facebook/5/array-and-strings/3008/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int start = 0, end = 0;
        map<char, int> m;
        int result = INT_MIN;
        bool allDistinct = true;
        for( ; end < s.length(); end++) {
            if(m.find(s[end]) == m.end() || m[s[end]] < start) {
                m[s[end]] = end;
            } else {
                allDistinct = false;
                result = max(result, end-start);
                start = m[s[end]] + 1;
                m[s[end]] = end;
            } 
        }
        result = max(result, end-start);
        return allDistinct ? s.length() : result;
    }
};
