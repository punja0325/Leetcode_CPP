/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 */

// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charMap;
        uint32_t maxLength = 0;
        for(uint32_t i = 0, start = 0; i < s.size(); i++) {
            if (charMap.count(s[i]) > 0 && charMap[s[i]] >= start)
            {
                start = charMap[s[i]] + 1;
            }
            charMap[s[i]] = i;
            maxLength = (maxLength > i - start + 1) ? maxLength : i - start + 1;
        }
        return maxLength;
    }

};
// @lc code=end

