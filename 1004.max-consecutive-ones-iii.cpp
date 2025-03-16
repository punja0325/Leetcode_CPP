/*
 * @lc app=leetcode id=1004 lang=cpp
 *
 * [1004] Max Consecutive Ones III
 *
 * https://leetcode.com/problems/max-consecutive-ones-iii/description/
 *
 * algorithms
 * Medium (62.93%)
 * Likes:    9240
 * Dislikes: 159
 * Total Accepted:    897.2K
 * Total Submissions: 1.4M
 * Testcase Example:  '[1,1,1,0,0,0,1,1,1,1,0]\n2'
 *
 * Given a binary array nums and an integer k, return the maximum number of
 * consecutive 1's in the array if you can flip at most k 0's.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
 * Output: 6
 * Explanation: [1,1,1,0,0,1,1,1,1,1,1]
 * Bolded numbers were flipped from 0 to 1. The longest subarray is
 * underlined.
 *
 * Example 2:
 *
 *
 * Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
 * Output: 10
 * Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
 * Bolded numbers were flipped from 0 to 1. The longest subarray is
 * underlined.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10^5
 * nums[i] is either 0 or 1.
 * 0 <= k <= nums.length
 *
 *
 */

// @lc code=start
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int MaxOnesLength = 0;
        int left = 0;
        int zeros = 0;
        for(int right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) {
                zeros++;
            }
            //if the number of zero exceeds k, shrink the windows from left
            while(zeros > k) {
                if (nums[left] == 0) {
                    zeros--; //Remove a zero from windows
                }
                left++; //Move the left boundry to the right
            }
            //update the maximum length of the valid windows
            MaxOnesLength = max(MaxOnesLength, right - left + 1);
        }
        return MaxOnesLength;
    }
};
// @lc code=end

