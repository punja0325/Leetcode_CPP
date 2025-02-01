/*
 * @lc app=leetcode id=136 lang=cpp
 *
 * [136] Single Number
 */

// @lc code=start
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        //hash map
        unordered_map <int, int> countMap;
        //Count element num and use it as key in the map
        for(int i = 0; i < nums.size(); i++) {
            if (countMap.count(nums[i]) > 0) countMap[nums[i]]++;
            else countMap[nums[i]] = 1;
        }
        for (auto it = countMap.begin(); it != countMap.end(); it++) {
            if (it->second == 1) return it->first;
        }
        return -1;
    }
};
// @lc code=end

