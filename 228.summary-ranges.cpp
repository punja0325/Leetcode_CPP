/*
 * @lc app=leetcode id=228 lang=cpp
 *
 * [228] Summary Ranges
 */

// @lc code=start
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        
        vector<string> res;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int j = i;
            while (j < n && nums[j] == nums[j-1] + 1) j++;
            
        
    }
};
// @lc code=end

