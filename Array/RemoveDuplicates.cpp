//https://leetcode.com/problems/remove-duplicates-from-sorted-array
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
     if(nums.size() <= 1) return nums.size();
     int curr = 1;
      int prev = nums[0];
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] == prev) continue;
            else {
                prev = nums[i];
                nums[curr++] = nums[i];
            }
        }
    return curr;
    }
};
