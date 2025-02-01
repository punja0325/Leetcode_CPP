/*
 * @lc app=leetcode id=242 lang=cpp
 *
 * [242] Valid Anagram
 */

// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> charCount;
        if (s.size() != t.size()) return false;
        for(int i = 0; i < s.size(); i++) {
            charCount[s[i]]++;
            charCount[t[i]]--;
        }
        for (auto count : charCount) {
            if (count.second != 0) return false;
        }
        return true;
    }
};
// @lc code=end

