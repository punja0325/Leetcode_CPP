/*
 * @lc app=leetcode id=22 lang=cpp
 *
 * [22] Generate Parentheses
 *
 * https://leetcode.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (74.49%)
 * Likes:    22128
 * Dislikes: 1028
 * Total Accepted:    2.3M
 * Total Submissions: 3M
 * Testcase Example:  '3'
 *
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 *
 *
 * Example 1:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 * Example 2:
 * Input: n = 1
 * Output: ["()"]
 *
 *
 * Constraints:
 *
 *
 * 1 <= n <= 8
 *
 *
 */

// @lc code=start
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string path;
        backtrack(n, 0, 0, path, result);
        return result;
    }
private:
    void backtrack(int n, int left, int right, string& path, vector<string>& result) {
        if (path.size() == 2 * n) {
            result.push_back(path);
            return;
        }
        if (left < n) {
            path.push_back('(');
            backtrack(n, left+1, right, path, result);
            path.pop_back();
        }
        if (right < left) {
            path.push_back(')');
            backtrack(n, left, right+1, path, result);
            path.pop_back();
        }
    }
};
// @lc code=end

