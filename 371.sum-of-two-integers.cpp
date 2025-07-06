/*
 * @lc app=leetcode id=371 lang=cpp
 *
 * [371] Sum of Two Integers
 *
 * https://leetcode.com/problems/sum-of-two-integers/description/
 *
 * algorithms
 * Medium (51.81%)
 * Likes:    4480
 * Dislikes: 5727
 * Total Accepted:    599.4K
 * Total Submissions: 1.1M
 * Testcase Example:  '1\n2'
 *
 * Given two integers a and b, return the sum of the two integers without using
 * the operators + and -.
 *
 *
 * Example 1:
 * Input: a = 1, b = 2
 * Output: 3
 * Example 2:
 * Input: a = 2, b = 3
 * Output: 5
 *
 *
 * Constraints:
 *
 *
 * -1000 <= a, b <= 1000
 *
 *
 */

// @lc code=start
class Solution {
public:
    int getSum(int a, int b) {
        while(b != 0) {
            int carry = (a & b) << 1; //carry
            a = a ^ b; //add without carry
            b = carry;
        }
        return a;
    }
};
// @lc code=end

