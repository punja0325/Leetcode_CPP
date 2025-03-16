/*
 * @lc app=leetcode id=238 lang=cpp
 *
 * [238] Product of Array Except Self
 *
 * https://leetcode.com/problems/product-of-array-except-self/description/
 *
 * algorithms
 * Medium (66.15%)
 * Likes:    23824
 * Dislikes: 1529
 * Total Accepted:    3.4M
 * Total Submissions: 5.1M
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given an integer array nums, return an array answer such that answer[i] is
 * equal to the product of all the elements of nums except nums[i].
 *
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit
 * integer.
 *
 * You must write an algorithm that runs in O(n) time and without using the
 * division operation.
 *
 *
 * Example 1:
 * Input: nums = [1,2,3,4]
 * Output: [24,12,8,6]
 * Example 2:
 * Input: nums = [-1,1,0,-3,3]
 * Output: [0,0,9,0,0]
 *
 *
 * Constraints:
 *
 *
 * 2 <= nums.length <= 10^5
 * -30 <= nums[i] <= 30
 * The input is generated such that answer[i] is guaranteed to fit in a 32-bit
 * integer.
 *
 *
 *
 * Follow up: Can you solve the problem in O(1) extra space complexity? (The
 * output array does not count as extra space for space complexity analysis.)
 *
 */

// @lc code=start
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prefix(nums.size()), suffix(nums.size());
        vector<int> ans(nums.size());
            prefix[0] = 1;
        suffix[nums.size() - 1] = 1;
        for(int i = 1; i < nums.size(); i++) {
            prefix[i] = prefix[i-1] * nums[i-1];
        }
        for(int i = nums.size() - 2; i >= 0; i--) {
            suffix[i] = suffix[i+1] * nums[i+1];
        }
        for(int i = 0; i < nums.size(); i++) {
            ans[i] = prefix[i] * suffix[i];
        }
        return ans;
    }
};
// @lc code=end

