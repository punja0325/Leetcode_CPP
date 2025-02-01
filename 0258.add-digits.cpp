/*
 * @lc app=leetcode id=258 lang=cpp
 *
 * [258] Add Digits
 */

// @lc code=start
class Solution {
public:
    int addDigits(int num) {
        while(num >= 10) {
            int sum = 0;
            while(num) {
                sum += num % 10;
                num /= 10;
            }
            num = sum;
        }
        return num;
    }
};
// @lc code=end

