/*
 * @lc app=leetcode id=125 lang=cpp
 *
 * [125] Valid Palindrome
 */

// @lc code=start
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while(left < right) {
            while (!isAlphabetOrNum(s.at(left)) && left < right) left++;
            while (!isAlphabetOrNum(s.at(right)) && left < right) right--;
            if (tolowerAlphabet(s.at(left)) != tolowerAlphabet(s.at(right))) return false;
            left++;
            right--;
        }
        return true;
    }
private:
    bool isAlphabetOrNum(char& a) {
        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a<= '9'))
        return true;
        return false;
    }
    char tolowerAlphabet(char & a) {
        if (a >= 'a' && a <= 'z') return a;
        if (a >= 'A' && a <= 'Z') return a-'A'+'a';
        return a - '0';
    }
};
// @lc code=end

