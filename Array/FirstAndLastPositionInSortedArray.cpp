https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array
class Solution {
public:
    int firstOccurence(vector<int> & nums, int low, int high, int target) {
        if(low > high) return -1;
        if(low == high) return nums[low] == target ? low : -1;
        if(high - 1 == low) {
            if(nums[low] == target) return low;
            else if(nums[high] == target) return high;
            else return -1;
        }
        int mid = low + (high-low)/2;
        if(nums[mid] < target) return firstOccurence(nums, mid+1, high, target);
        else if(nums[mid] > target) return firstOccurence(nums, low, mid-1, target);
        else if(nums[mid] == target) {
            return firstOccurence(nums, low, mid, target);
        }
        return -1;
    }
    int lastOccurence(vector<int> & nums, int low, int high, int target) {
        if(low > high) return -1;
        if(low == high) return nums[low] == target ? low : -1;
        if(high - 1 == low) {
            if(nums[high] == target) return high;
            else if(nums[low] == target) return low;
            else return -1;
        }
        int mid = low + (high-low)/2;
        if(nums[mid] < target) return lastOccurence(nums, mid+1, high, target);
        else if(nums[mid] > target) return lastOccurence(nums, low, mid-1, target);
        else if(nums[mid] == target) {
            return lastOccurence(nums, mid, high, target);
        }
        return -1;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result;
        result.push_back(firstOccurence(nums, 0, nums.size()-1, target));
         result.push_back(lastOccurence(nums, 0, nums.size()-1, target));
        return result;
    }
};
