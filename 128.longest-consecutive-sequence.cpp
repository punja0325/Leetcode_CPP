/*
 * @lc app=leetcode id=128 lang=cpp
 *
 * [128] Longest Consecutive Sequence
 *
 * https://leetcode.com/problems/longest-consecutive-sequence/description/
 *
 * algorithms
 * Medium (47.43%)
 * Likes:    21147
 * Dislikes: 1127
 * Total Accepted:    2.4M
 * Total Submissions: 5.1M
 * Testcase Example:  '[100,4,200,1,3,2]'
 *
 * Given an unsorted array of integers nums, return the length of the longest
 * consecutive elements sequence.
 * 
 * You must write an algorithm that runs in O(n) time.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [100,4,200,1,3,2]
 * Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
 * Therefore its length is 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,3,7,2,5,8,4,6,0,1]
 * Output: 9
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,0,1,2]
 * Output: 3
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 * 
 * 
 */

// @lc code=start

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> uSet(nums.begin(), nums.end());

        int maxLen = 0;
        for (int i: uSet){
            if (uSet.find(i-1) == uSet.end()){
                int len=1;
                while (uSet.find(i+len) != uSet.end()) len++;

                maxLen = max(maxLen, len);
            }
        }

        return maxLen;
    }
};
// @lc code=end

