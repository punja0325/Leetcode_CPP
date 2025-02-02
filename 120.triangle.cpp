/*
 * @lc app=leetcode id=120 lang=cpp
 *
 * [120] Triangle
 *
 * https://leetcode.com/problems/triangle/description/
 *
 * algorithms
 * Medium (58.37%)
 * Likes:    9838
 * Dislikes: 571
 * Total Accepted:    911.9K
 * Total Submissions: 1.6M
 * Testcase Example:  '[[2],[3,4],[6,5,7],[4,1,8,3]]'
 *
 * Given a triangle array, return the minimum path sum from top to bottom.
 *
 * For each step, you may move to an adjacent number of the row below. More
 * formally, if you are on index i on the current row, you may move to either
 * index i or index i + 1 on the next row.
 *
 *
 * Example 1:
 *
 *
 * Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
 * Output: 11
 * Explanation: The triangle looks like:
 * ⁠  2
 * ⁠ 3 4
 * ⁠6 5 7
 * 4 1 8 3
 * The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined
 * above).
 *
 *
 * Example 2:
 *
 *
 * Input: triangle = [[-10]]
 * Output: -10
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= triangle.length <= 200
 * triangle[0].length == 1
 * triangle[i].length == triangle[i - 1].length + 1
 * -10^4 <= triangle[i][j] <= 10^4
 *
 *
 *
 * Follow up: Could you do this using only O(n) extra space, where n is the
 * total number of rows in the triangle?
 */

// @lc code=start
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int m = triangle.size();
        int n = m;
        if (m == 0) return 0;
        else if (m == 1) return triangle[0][0];
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = triangle[0][0];
        int row_max;
        for (int row = 1; row < m; ++row) {
            row_max = INT_MAX;
            for (int column = 0; column <= row; ++column) {
                //boundary case:
                if (column == 0) {
                    dp[row][column] = dp[row-1][column] + triangle[row][column];
                } else if (column == row) {
                    dp[row][column] = dp[row-1][column-1] + triangle[row][column];
                } else {
                    int left = dp[row-1][column-1];
                    int right = dp[row-1][column];
                    dp[row][column] = min(left, right) + triangle[row][column];
                }
                row_max = min(row_max, dp[row][column]);
            }
        }
        return row_max;
    }
};
// @lc code=end

