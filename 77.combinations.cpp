/*
 * @lc app=leetcode id=77 lang=cpp
 *
 * [77] Combinations
 *
 * https://leetcode.com/problems/combinations/description/
 *
 * algorithms
 * Medium (72.02%)
 * Likes:    8434
 * Dislikes: 234
 * Total Accepted:    1M
 * Total Submissions: 1.5M
 * Testcase Example:  '4\n2'
 *
 * Given two integers n and k, return all possible combinations of k numbers
 * chosen from the range [1, n].
 * 
 * You may return the answer in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 4, k = 2
 * Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 * Explanation: There are 4 choose 2 = 6 total combinations.
 * Note that combinations are unordered, i.e., [1,2] and [2,1] are considered
 * to be the same combination.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1, k = 1
 * Output: [[1]]
 * Explanation: There is 1 choose 1 = 1 total combination.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 20
 * 1 <= k <= n
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> temp;
        backtrack(n, k, 0, temp, res);
        return res;
    }
private:
    void backtrack(int n, int k, int start, vector<int>& temp, vector<vector<int>>& res) {
        // Check if the condition is met
        if (temp.size() == k) {
            res.push_back(temp);
            return;
        }

        // Explore all possible solution
        for(int i = start + 1; i <= n; i++) {
            temp.push_back(i);
            backtrack(n, k, i, temp, res);
            temp.pop_back();
        }

    }
};
// @lc code=end

