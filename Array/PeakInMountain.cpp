class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        if(arr.size() == 1) return arr[0];
        int low = 0, high = arr.size()-1;
        while(low <= high)
        {
            if(low == high) return low;
            int mid = low + (high-low)/2;
            if(mid > 0 && arr[mid-1] < arr[mid] && mid < arr.size() && arr[mid] > arr[mid+1]) return mid;
           else if(mid > 0 && arr[mid-1] < arr[mid] && mid < arr.size() && arr[mid] < arr[mid+1]) low = mid;
            else if(mid > 0 && arr[mid-1] > arr[mid] && mid < arr.size() && arr[mid] > arr[mid+1]) high = mid;
            
        }
        return -1;
    }
};
