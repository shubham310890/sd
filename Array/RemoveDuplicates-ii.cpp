// https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
       if(nums.size() <= 2) return nums.size();
        int curr = 2;
        int prev_1 = nums[0], prev_2 = nums[1];
        for(int i = 2; i < nums.size(); i++) {
            //cout << prev_1 << " " << prev_2 << endl;
            if(nums[i] == prev_1) continue;
            else {
                prev_1 = prev_2;
                prev_2 = nums[i];
               // cout << prev_1 << " in " << prev_2 << endl;
                nums[curr] = nums[i] ;
                curr++;
            }
        }
        return curr;
    }
};
