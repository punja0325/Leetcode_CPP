/*
 * @lc app=leetcode id=76 lang=cpp
 *
 * [76] Minimum Window Substring
 *
 * https://leetcode.com/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (44.41%)
 * Likes:    18655
 * Dislikes: 776
 * Total Accepted:    1.7M
 * Total Submissions: 3.7M
 * Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * Given two strings s and t of lengths m and n respectively, return the
 * minimum window substring of s such that every character in t (including
 * duplicates) is included in the window. If there is no such substring, return
 * the empty string "".
 * 
 * The testcases will be generated such that the answer is unique.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 * Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C'
 * from string t.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "a", t = "a"
 * Output: "a"
 * Explanation: The entire string s is the minimum window.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "a", t = "aa"
 * Output: ""
 * Explanation: Both 'a's from t must be included in the window.
 * Since the largest window of s only has one 'a', return empty string.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == s.length
 * n == t.length
 * 1 <= m, n <= 10^5
 * s and t consist of uppercase and lowercase English letters.
 * 
 * 
 * 
 * Follow up: Could you find an algorithm that runs in O(m + n) time?
 * 
 */

// @lc code=start
class Solution {
public:
    string minWindow(string s, string t) {
        int matches = 0;
        int minLen = INT_MAX;
        int minStart = 0;
        unordered_map<char, int> tFreq , windowFreq;
        for(char c : t) {
            tFreq[c]++;
        }
        int t_size = tFreq.size();
        int left = 0;
        for(int right = 0; right < s.size(); right++) {
            char rightChar = s[right];
            //if (tFreq.count(rightChar) > 0) {
            cout << tFreq[rightChar] << endl;
            if (tFreq[rightChar] > 0) {
                cout << "Hello" << endl;
                windowFreq[rightChar]++;
                if (windowFreq[rightChar] == tFreq[rightChar]) {
                    matches++;
                }
            }
            while(matches == t_size) {
                int len = right - left + 1;
                if (len < minLen) {
                    minLen = len;
                    minStart = left;
                }
                char leftChar = s[left];
                //if (tFreq.count(leftChar) > 0) {
                if (tFreq[leftChar] > 0) {
                    if (windowFreq[leftChar] == tFreq[leftChar]) {
                        matches--;
                    }
                    windowFreq[leftChar]--;
                }
                left++;
            }
        }
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
};
// @lc code=end

