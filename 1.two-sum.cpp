/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for(int i = 0; i < nums.size(); i++) {
            int complement = target - nums.at(i);
            if (map.count(complement)) {
                return {map[complement], i};
            }
            map[nums.at(i)] = i;
        }
        return {}; // no solution
    }
};
// @lc code=end

