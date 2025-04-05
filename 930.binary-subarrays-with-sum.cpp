/*
 * @lc app=leetcode id=930 lang=cpp
 *
 * [930] Binary Subarrays With Sum
 *
 * https://leetcode.com/problems/binary-subarrays-with-sum/description/
 *
 * algorithms
 * Medium (64.71%)
 * Likes:    4225
 * Dislikes: 143
 * Total Accepted:    337.6K
 * Total Submissions: 518.2K
 * Testcase Example:  '[1,0,1,0,1]\n2'
 *
 * Given a binary array nums and an integer goal, return the number of
 * non-empty subarrays with a sum goal.
 * 
 * A subarray is a contiguous part of the array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,0,1,0,1], goal = 2
 * Output: 4
 * Explanation: The 4 subarrays are bolded and underlined below:
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,0,0,0,0], goal = 0
 * Output: 15
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 3 * 10^4
 * nums[i] is either 0 or 1.
 * 0 <= goal <= nums.length
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int> prefixSumCount;
        prefixSumCount[0] = 1;
        int count = 0;
        int sum = 0;
        for(int num : nums) {
            sum += num;
            if (prefixSumCount.find(sum - goal) != prefixSumCount.end()) {
                count += prefixSumCount[sum - goal];
            }
            prefixSumCount[sum]++;
        }
        return count;
    }
};
// @lc code=end

