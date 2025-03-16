/*
 * @lc app=leetcode id=287 lang=cpp
 *
 * [287] Find the Duplicate Number
 *
 * https://leetcode.com/problems/find-the-duplicate-number/description/
 *
 * algorithms
 * Medium (62.15%)
 * Likes:    24064
 * Dislikes: 5095
 * Total Accepted:    2.1M
 * Total Submissions: 3.3M
 * Testcase Example:  '[1,3,4,2,2]'
 *
 * Given an array of integers nums containing n + 1 integers where each integer
 * is in the range [1, n] inclusive.
 * 
 * There is only one repeated number in nums, return this repeated number.
 * 
 * You must solve the problem without modifying the array nums and using only
 * constant extra space.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,4,2,2]
 * Output: 2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,1,3,4,2]
 * Output: 3
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [3,3,3,3,3]
 * Output: 3
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^5
 * nums.length == n + 1
 * 1 <= nums[i] <= n
 * All the integers in nums appear only once except for precisely one integer
 * which appears two or more times.
 * 
 * 
 * 
 * Follow up:
 * 
 * 
 * How can we prove that at least one duplicate number must exist in nums?
 * Can you solve the problem in linear runtime complexity?
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0], fast = nums[0];
        slow = nums[slow];
        fast = nums[nums[fast]];
        //find metting point
        while(slow != fast) {
            cout << "slow:" << slow << " fast:" << fast << endl;
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        cout << slow << endl;
        // find entry point of cycle
        slow = nums[0];
        while(slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return fast;
    }
};
// @lc code=end

