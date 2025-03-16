/*
 * @lc app=leetcode id=567 lang=cpp
 *
 * [567] Permutation in String
 *
 * https://leetcode.com/problems/permutation-in-string/description/
 *
 * algorithms
 * Medium (44.34%)
 * Likes:    12173
 * Dislikes: 474
 * Total Accepted:    1.2M
 * Total Submissions: 2.5M
 * Testcase Example:  '"ab"\n"eidbaooo"'
 *
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1,
 * or false otherwise.
 *
 * In other words, return true if one of s1's permutations is the substring of
 * s2.
 *
 *
 * Example 1:
 *
 *
 * Input: s1 = "ab", s2 = "eidbaooo"
 * Output: true
 * Explanation: s2 contains one permutation of s1 ("ba").
 *
 *
 * Example 2:
 *
 *
 * Input: s1 = "ab", s2 = "eidboaoo"
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s1.length, s2.length <= 10^4
 * s1 and s2 consist of lowercase English letters.
 *
 *
 */

// @lc code=start
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> s1Freq, windowFreq;
        int left = 0;
        int matched = 0;
        for(char c : s1) s1Freq[c]++;
        for(int right = 0; right < s2.size(); right++) {
            //maintain sliding wondow, and its size equals to s1.size()
            windowFreq[s2[right]]++;
            if (right - left + 1 > s1.size()) {
                windowFreq[s2[left]]--;
                if (windowFreq[s2[left]] == 0) {
                    windowFreq.erase(s2[left]);
                }
                left++;
            }
            if (s1Freq == windowFreq) {
                return true;
            }
        }
        return false;
    }
};
// @lc code=end

