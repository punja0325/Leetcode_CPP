/*
 * @lc app=leetcode id=78 lang=cpp
 *
 * [78] Subsets
 *
 * https://leetcode.com/problems/subsets/description/
 *
 * algorithms
 * Medium (79.99%)
 * Likes:    17830
 * Dislikes: 296
 * Total Accepted:    2.3M
 * Total Submissions: 2.9M
 * Testcase Example:  '[1,2,3]'
 *
 * Given an integer array nums of unique elements, return all possible subsets
 * (the power set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [0]
 * Output: [[],[0]]
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 * All the numbers of nums are unique.
 *
 *
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> temp;
        backtrack(nums, 0, temp, res);
        return res;
    }
private:
    void backtrack(vector<int>& nums, int start, vector<int>& temp, vector<vector<int>>& res) {
        //Check if the condition is met (No codition)
        res.push_back(temp);

        //Explore all possible solution
        for(int i = start; i < nums.size(); i++) {
            temp.push_back(nums[i]);
            backtrack(nums, i + 1, temp, res);
            temp.pop_back();
        }
    }
};
// @lc code=end

