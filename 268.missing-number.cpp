/*
 * @lc app=leetcode id=268 lang=cpp
 *
 * [268] Missing Number
 *
 * https://leetcode.com/problems/missing-number/description/
 *
 * algorithms
 * Easy (66.73%)
 * Likes:    13091
 * Dislikes: 3409
 * Total Accepted:    3M
 * Total Submissions: 4.3M
 * Testcase Example:  '[3,0,1]'
 *
 * Given an array nums containing n distinct numbers in the range [0, n],
 * return the only number in the range that is missing from the array.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [3,0,1]
 *
 * Output: 2
 *
 * Explanation:
 *
 * n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is
 * the missing number in the range since it does not appear in nums.
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [0,1]
 *
 * Output: 2
 *
 * Explanation:
 *
 * n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is
 * the missing number in the range since it does not appear in nums.
 *
 *
 * Example 3:
 *
 *
 * Input: nums = [9,6,4,2,3,5,7,0,1]
 *
 * Output: 8
 *
 * Explanation:
 *
 * n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is
 * the missing number in the range since it does not appear in
 * nums.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * Constraints:
 *
 *
 * n == nums.length
 * 1 <= n <= 10^4
 * 0 <= nums[i] <= n
 * All the numbers of nums are unique.
 *
 *
 *
 * Follow up: Could you implement a solution using only O(1) extra space
 * complexity and O(n) runtime complexity?
 *
 */

// @lc code=start
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        long long int sum = (n * (n+1)) / 2;
        for (auto num : nums) {
            sum -= num;
        }
        return sum;
    }
};
// @lc code=end

