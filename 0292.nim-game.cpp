/*
 * @lc app=leetcode id=292 lang=cpp
 *
 * [292] Nim Game
 */

// @lc code=start
//#define METHOD_1
#define METHOD_2
class Solution {
public:
    bool canWinNim(int n) {
        //win: 1/2/3..... return true;
        //lose: 4/8....   return false;
        //==> Check if n is divisible by 4
        #ifdef METHOD_1
        if (n <= 3) return true;
        if (n % 4 == 0) return false;
        return true;
        #elif defined(METHOD_2)
        return n & 3;
        #endif
    }
};
// @lc code=end

