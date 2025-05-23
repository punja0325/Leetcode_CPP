/*
 * @lc app=leetcode id=75 lang=cpp
 *
 * [75] Sort Colors
 *
 * https://leetcode.com/problems/sort-colors/description/
 *
 * algorithms
 * Medium (62.15%)
 * Likes:    19990
 * Dislikes: 712
 * Total Accepted:    2.9M
 * Total Submissions: 4.3M
 * Testcase Example:  '[2,0,2,1,1,0]'
 *
 * Given an array nums with n objects colored red, white, or blue, sort them
 * in-place so that objects of the same color are adjacent, with the colors in
 * the order red, white, and blue.
 *
 * We will use the integers 0, 1, and 2 to represent the color red, white, and
 * blue, respectively.
 *
 * You must solve this problem without using the library's sort function.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [2,0,1]
 * Output: [0,1,2]
 *
 *
 *
 * Constraints:
 *
 *
 * n == nums.length
 * 1 <= n <= 300
 * nums[i] is either 0, 1, or 2.
 *
 *
 *
 * Follow up: Could you come up with a one-pass algorithm using only constant
 * extra space?
 *
 */

// @lc code=start
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, mid = 0, right = nums.size() - 1;
        while(mid <= right) {
            //0, 1, 2
            if (nums[mid] == 0) {
                swap(nums[left++], nums[mid++]);
            } else if (nums[mid] == 2) {
                swap(nums[mid], nums[right--]);
            } else {
                mid++;
            }
        }

    };
};;
// @lc code=end

