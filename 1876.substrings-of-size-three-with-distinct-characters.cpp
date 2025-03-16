/*
 * @lc app=leetcode id=1876 lang=cpp
 *
 * [1876] Substrings of Size Three with Distinct Characters
 *
 * https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/description/
 *
 * algorithms
 * Easy (73.19%)
 * Likes:    1569
 * Dislikes: 48
 * Total Accepted:    154.8K
 * Total Submissions: 206.2K
 * Testcase Example:  '"xyzzaz"'
 *
 * A string is good if there are no repeated characters.
 *
 * Given a string s​​​​​, return the number of good substrings of length three
 * in s​​​​​​.
 *
 * Note that if there are multiple occurrences of the same substring, every
 * occurrence should be counted.
 *
 * A substring is a contiguous sequence of characters in a string.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "xyzzaz"
 * Output: 1
 * Explanation: There are 4 substrings of size 3: "xyz", "yzz", "zza", and
 * "zaz".
 * The only good substring of length 3 is "xyz".
 *
 *
 * Example 2:
 *
 *
 * Input: s = "aababcabc"
 * Output: 4
 * Explanation: There are 7 substrings of size 3: "aab", "aba", "bab", "abc",
 * "bca", "cab", and "abc".
 * The good substrings are "abc", "bca", "cab", and "abc".
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 100
 * s​​​​​​ consists of lowercase English letters.
 *
 *
 */

// @lc code=start
class Solution {
public:
    int countGoodSubstrings(string s) {
        unordered_map<char, int> windowFreq;
        int ans = 0, left = 0;
        for(int right = 0; right < s.length(); right++) {
            windowFreq[s[right]]++;
            if (right - left + 1 == 3) {
                if (windowFreq[s[right]] == && windowFreq[s[left]] == 1 && windowFreq[left + 1] == 1) {
                    ans++;
                }
                windowFreq[s[left]]--;
                left++;
            }
        }
    }
};
// @lc code=end

