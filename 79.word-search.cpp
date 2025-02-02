/*
 * @lc app=leetcode id=79 lang=cpp
 *
 * [79] Word Search
 *
 * https://leetcode.com/problems/word-search/description/
 *
 * algorithms
 * Medium (44.35%)
 * Likes:    16388
 * Dislikes: 694
 * Total Accepted:    1.9M
 * Total Submissions: 4.4M
 * Testcase Example:  '[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]\n"ABCCED"'
 *
 * Given an m x n grid of characters board and a string word, return true if
 * word exists in the grid.
 *
 * The word can be constructed from letters of sequentially adjacent cells,
 * where adjacent cells are horizontally or vertically neighboring. The same
 * letter cell may not be used more than once.
 *
 *
 * Example 1:
 *
 *
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word
 * = "ABCCED"
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word
 * = "SEE"
 * Output: true
 *
 *
 * Example 3:
 *
 *
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word
 * = "ABCB"
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * m == board.length
 * n = board[i].length
 * 1 <= m, n <= 6
 * 1 <= word.length <= 15
 * board and word consists of only lowercase and uppercase English letters.
 *
 *
 *
 * Follow up: Could you use search pruning to make your solution faster with a
 * larger board?
 *
 */

// @lc code=start
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();     // Get the number of rows in the board
        int n = board[0].size();  // Get the number of columns in the board
        vector<vector<bool>> visited(m, vector<bool>(n, false)); // 2D array to track visited positions
        // Iterate through each cell in the board as a starting point
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) { // If the current cell matches the first character of the word
                    if (backtrack(board, word, i, j, 0, visited)) { // Start backtracking from this cell
                        return true; // Word found, return true
                    }
                }
            }
        }
        return false;// Word not found after checking all starting points
    }
private:
    bool backtrack(vector<vector<char>>& board, string& word, int x, int y, int index, vector<vector<bool>>& visited) {
        // If all characters of the word are matched
        if (index == word.size()) return true;

        // Check if current position is out of bounds or already visited
        if (x >= board.size() || y >= board[0].size() || visited[x][y]) return false;

        // If current character does not match
        if (board[x][y] != word[index]) return false;

        // Mark current position as visited
        visited[x][y] = true;

        // Recursively search in all four directions
        bool found = backtrack(board, word, x+1, y, index +1, visited) ||
                     backtrack(board, word, x-1, y, index +1, visited) ||
                     backtrack(board, word, x, y+1, index +1, visited) ||
                     backtrack(board, word, x, y-1, index +1, visited);
        // Unmark current position as part of backtracking
        visited[x][y] = false;

        return found;// Return whether the word is found
    }
};

// @lc code=end

