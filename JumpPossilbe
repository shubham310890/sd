class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size() <= 1) return true;
        int maxReach = nums[0], steps = nums[0], jumps = 1;
        if(maxReach == 0) return false;
        for(int i = 1; i < nums.size(); i++)
        {
            maxReach = maxReach > i + nums[i] ? maxReach : i + nums[i];
            if(i >= maxReach && i != nums.size()-1) return false;
            steps--;
            if(steps == 0)
            {
                jumps++;
                steps = maxReach - i;
            }
        }
        return jumps;
    }
};
