/*
 * @lc app=leetcode id=172 lang=cpp
 *
 * [172] Factorial Trailing Zeroes
 *
 * https://leetcode.com/problems/factorial-trailing-zeroes/description/
 *
 * algorithms
 * Medium (44.31%)
 * Likes:    3363
 * Dislikes: 1974
 * Total Accepted:    557.6K
 * Total Submissions: 1.2M
 * Testcase Example:  '3'
 *
 * Given an integer n, return the number of trailing zeroes in n!.
 * 
 * Note that n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3
 * Output: 0
 * Explanation: 3! = 6, no trailing zero.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 5
 * Output: 1
 * Explanation: 5! = 120, one trailing zero.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 0
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= n <= 10^4
 * 
 * 
 * 
 * Follow up: Could you write a solution that works in logarithmic time
 * complexity?
 * 
 */

// @lc code=start
class Solution {
public:
    int trailingZeroes(int n) {
        int count = 0;
        while(n >= 5) {
            n /= 5;
            count += n;
        }
        return count;
    }
};
// @lc code=end

