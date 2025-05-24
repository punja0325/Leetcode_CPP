/*
 * @lc app=leetcode id=20 lang=cpp
 *
 * [20] Valid Parentheses
 *
 * https://leetcode.com/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (40.55%)
 * Likes:    25729
 * Dislikes: 1876
 * Total Accepted:    6M
 * Total Submissions: 14.3M
 * Testcase Example:  '"()"'
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 *
 * An input string is valid if:
 *
 *
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * Every close bracket has a corresponding open bracket of the same type.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: s = "()"
 *
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: s = "()[]{}"
 *
 * Output: true
 *
 *
 * Example 3:
 *
 *
 * Input: s = "(]"
 *
 * Output: false
 *
 *
 * Example 4:
 *
 *
 * Input: s = "([])"
 *
 * Output: true
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 10^4
 * s consists of parentheses only '()[]{}'.
 *
 *
 */

// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            } else if (c == ')' || c == ']' || c == '}') {
                if (!st.empty()) {
                    char top_c = st.top(); st.pop();
                    if ((c == ')' && top_c != '(') ||
                        (c == ']' && top_c != '[') ||
                        (c == '}' && top_c != '{')) {
                        return false;
                    }
                    continue;
                }
                return false;
            }
        }
        if (st.empty()) return true;
        return false;
    }
};
// @lc code=end

