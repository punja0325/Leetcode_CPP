/*
 * @lc app=leetcode id=46 lang=cpp
 *
 * [46] Permutations
 *
 * https://leetcode.com/problems/permutations/description/
 *
 * algorithms
 * Medium (79.90%)
 * Likes:    19608
 * Dislikes: 345
 * Total Accepted:    2.4M
 * Total Submissions: 3M
 * Testcase Example:  '[1,2,3]'
 *
 * Given an array nums of distinct integers, return all the possible
 * permutations. You can return the answer in any order.
 *
 *
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 * Example 2:
 * Input: nums = [0,1]
 * Output: [[0,1],[1,0]]
 * Example 3:
 * Input: nums = [1]
 * Output: [[1]]
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 6
 * -10 <= nums[i] <= 10
 * All the integers of nums are unique.
 *
 *
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        /*
        - Use backtracking to generate all permutations.
        - Swap elements to explore all possible arrangements.
        - Use a start index to track the current position in the array.
        */
        vector<vector<int>> res;
        backtrack(nums, 0, res); // Start backtracking from index 0
        return res;
    }
private:
    void backtrack(vector<int>& nums, int start, vector<vector<int>>& res) {
        // If we've reached the end of the array, add the current permutation to the result
        if (start == nums.size()) {
            res.push_back(nums);
            return;
        }

        // Explore all possible permutations by swapping elements
        for(int i = start; i < nums.size(); i++) {
            swap(nums[start], nums[i]);
            backtrack(nums, start + 1,  res); // Recurse on the next position
            swap(nums[start], nums[i]); // Backtrack: undo the swap
        }
    }

};

// @lc code=end

