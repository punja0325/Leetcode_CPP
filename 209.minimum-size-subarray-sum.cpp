/*
 * @lc app=leetcode id=209 lang=cpp
 *
 * [209] Minimum Size Subarray Sum
 *
 * https://leetcode.com/problems/minimum-size-subarray-sum/description/
 *
 * algorithms
<<<<<<< HEAD
 * Medium (47.06%)
 * Likes:    13172
 * Dislikes: 477
 * Total Accepted:    1.3M
 * Total Submissions: 2.7M
=======
 * Medium (48.51%)
 * Likes:    13186
 * Dislikes: 478
 * Total Accepted:    1.3M
 * Total Submissions: 2.8M
>>>>>>> c25edc70ecb797998d276de122dd87b8302d1c88
 * Testcase Example:  '7\n[2,3,1,2,4,3]'
 *
 * Given an array of positive integers nums and a positive integer target,
 * return the minimal length of a subarray whose sum is greater than or equal
 * to target. If there is no such subarray, return 0 instead.
<<<<<<< HEAD
 *
 *
 * Example 1:
 *
 *
=======
 * 
 * 
 * Example 1:
 * 
 * 
>>>>>>> c25edc70ecb797998d276de122dd87b8302d1c88
 * Input: target = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: The subarray [4,3] has the minimal length under the problem
 * constraint.
<<<<<<< HEAD
 *
 *
 * Example 2:
 *
 *
 * Input: target = 4, nums = [1,4,4]
 * Output: 1
 *
 *
 * Example 3:
 *
 *
 * Input: target = 11, nums = [1,1,1,1,1,1,1,1]
 * Output: 0
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= target <= 10^9
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^4
 *
 *
 *
=======
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: target = 4, nums = [1,4,4]
 * Output: 1
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: target = 11, nums = [1,1,1,1,1,1,1,1]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= target <= 10^9
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^4
 * 
 * 
 * 
>>>>>>> c25edc70ecb797998d276de122dd87b8302d1c88
 * Follow up: If you have figured out the O(n) solution, try coding another
 * solution of which the time complexity is O(n log(n)).
 */

// @lc code=start
class Solution {
public:
<<<<<<< HEAD
    int minSubArrayLen(int target, std::vector<int>& nums) {
        int min_length = INT_MAX;
        int current_sum = 0;
        int left = 0;

        for (int right = 0; right < nums.size(); ++right) {
            current_sum += nums[right];

            // 缩小窗口，直到current_sum < target，或者left不能再右移
            while (current_sum >= target) {
                // 更新最小长度
                min_length = std::min(min_length, right - left + 1);
                // 移动左指针，尝试找到更小的窗口
                current_sum -= nums[left];
                left++;
            }
        }

        return min_length != INT_MAX ? min_length : 0;
=======
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = 0;
        int minLen = INT_MAX;
        int l = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            while(sum >= target && l <= i) {
                minLen = min(minLen, i - l + 1);
                sum -= nums[l];
                l++;
            }
        }
        return (minLen == INT_MAX) ? 0 : minLen;
>>>>>>> c25edc70ecb797998d276de122dd87b8302d1c88
    }
};
// @lc code=end

