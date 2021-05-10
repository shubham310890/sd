//https://leetcode.com/explore/interview/card/google/59/array-and-strings/3054/
class Solution {
public:
    int helper(string s, int k){
        if(s.length() <= 1) return s.length();
        map<char, int> m;
        int start = 0, end = 0, counter = 0, result = 0;
        m[s[0]] = 1;
        counter = 1;
        for(end = 1 ; end < s.length(); end++) {
            //cout << end << endl;
            if(m.find(s[end]) == m.end()) {
                m[s[end]] = 1;
                counter++;
            } else {
                m[s[end]]++;
            }
            while(counter > k) {
                if(m[s[start]] == 1) {
                    counter--;
                    m.erase(s[start]);
                } else {
                    m[s[start]]--;
                }
                start++;
            }
            result = result > end-start+1 ? result : end-start+1;
        }
        return result;
    }
    int lengthOfLongestSubstringTwoDistinct(string s) {
       return helper(s,2);
    }
};
