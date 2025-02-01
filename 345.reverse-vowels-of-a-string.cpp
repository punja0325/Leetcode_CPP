/*
 * @lc app=leetcode id=345 lang=cpp
 *
 * [345] Reverse Vowels of a String
 */

// @lc code=start
class Solution {
public:
    string reverseVowels(string s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            while (l < r && !isVowels(s[l])) l++;
            while (l < r && !isVowels(s[r])) r--;
            char t = s[l];
            s[l] = s[r];
            s[r] = t;
            l++;
            r--;
        }
        return s;
    }
private:
    bool isVowels(char& c) {
        const char vowels[] = {'a','A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};
        for(int i = 0; i < sizeof(vowels)/sizeof(char); i++) {
            if (vowels[i] == c) return true;
        }
        return false;
    }
};
// @lc code=end

