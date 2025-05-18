/*
 * @lc app=leetcode id=1399 lang=cpp
 *
 * [1399] Count Largest Group
 *
 * https://leetcode.com/problems/count-largest-group/description/
 *
 * algorithms
 * Easy (66.56%)
 * Likes:    666
 * Dislikes: 1121
 * Total Accepted:    123.1K
 * Total Submissions: 167K
 * Testcase Example:  '13'
 *
 * You are given an integer n.
 * 
 * Each number from 1 to n is grouped according to the sum of its digits.
 * 
 * Return the number of groups that have the largest size.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 13
 * Output: 4
 * Explanation: There are 9 groups in total, they are grouped according sum of
 * its digits of numbers from 1 to 13:
 * [1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
 * There are 4 groups with largest size.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2
 * Output: 2
 * Explanation: There are 2 groups [1], [2] of size 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^4
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int countLargestGroup(int n) {
        unordered_map<int, int> map;
        int maxSize = 0;
        for(int i = 1; i <= n; i++) {
            int key = getkey(i);
            map[key]++;
            maxSize = max(map[key], maxSize);
        }
        int result = 0;
        for(auto [key, value] : map) {
            if (value == maxSize) result++;
        }
        return result;
    }
    int getkey(int n) {
        int res = 0;
        while(n) {
            res += (n % 10);
            n /= 10;
        }
        return res;
    }
};
// @lc code=end

