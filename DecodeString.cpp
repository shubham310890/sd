class Solution {
public:
    int numDecodings(string s) {
        vector<int> decode(s.length()+1, 0);
        decode[0] = 1;
        decode[1] = stoi(s.substr(0,1)) > 0 ? 1 : 0;
        if(decode[1] == 0) return 0;
        for(int i = 1; i < s.length(); i++) {
            int last = stoi(s.substr(i-1,1))*10 + stoi(s.substr(i,1));
            if(stoi(s.substr(i,1)) > 0)
               decode[i+1] += decode[i];
            if(last >= 10 && last <= 26) 
               decode[i+1] += decode[i-1];
        }
        // for(int i = 0; i < s.length(); i++) cout << decode[i] << " ";
        // cout << endl;
        return decode[s.length()];
    }
};
