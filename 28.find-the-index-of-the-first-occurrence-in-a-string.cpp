/*
 * @lc app=leetcode id=28 lang=cpp
 *
 * [28] Find the Index of the First Occurrence in a String
 *
 * https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
 *
 * algorithms
 * Easy (44.23%)
 * Likes:    6699
 * Dislikes: 497
 * Total Accepted:    3.3M
 * Total Submissions: 7.4M
 * Testcase Example:  '"sadbutsad"\n"sad"'
 *
 * Given two strings needle and haystack, return the index of the first
 * occurrence of needle in haystack, or -1 if needle is not part of
 * haystack.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: haystack = "sadbutsad", needle = "sad"
 * Output: 0
 * Explanation: "sad" occurs at index 0 and 6.
 * The first occurrence is at index 0, so we return 0.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: haystack = "leetcode", needle = "leeto"
 * Output: -1
 * Explanation: "leeto" did not occur in "leetcode", so we return -1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= haystack.length, needle.length <= 10^4
 * haystack and needle consist of only lowercase English characters.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int strStr(string haystack, string needle) {
        #if 1
        if (needle.empty()) return 0;

        // Step1: Build LPS array
        vector<int> lps = buildLPS(needle);
        //Step2: KMP search
        int i = 0, j = 0;
        while(i < haystack.size()) {
            if (haystack[i] == needle[j]) {
                i++, j++;
                if (j == needle.size()) return i - j;
            } else {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return -1;

        #else
        int n = haystack.size(), m = needle.size();
        if (m == 0) return 0;
        for(int i = 0; i <= n - m; i++) {
            if (needle == haystack.substr(i, m))
                return i;
        }
        return -1;
        #endif        
    }
private:
    vector<int> buildLPS(string pattern) {
        vector<int> lps(pattern.size(), 0);
        int len = 0;
        for(int i = 1; i < pattern.size();) {
            if (pattern[i] == pattern[len]) {
                lps[i++] = ++len;
            } else {
                if (len == 0) {
                    lps[i++] = 0;
                } else {
                    len = lps[len - 1];
                }
            }
        }
        return lps;
    }
};
// @lc code=end

