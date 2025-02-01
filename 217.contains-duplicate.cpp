/*
 * @lc app=leetcode id=217 lang=cpp
 *
 * [217] Contains Duplicate
 */

// @lc code=start
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        //hash map
        unordered_map <int, int> countMap;
        //Count element num and use it as key in the map
        for(int i = 0; i < nums.size(); i++) {
            if (countMap.count(nums[i]) > 0) return true;
            countMap[nums[i]] = i;
        }
        return false;
    }
};
// @lc code=end

