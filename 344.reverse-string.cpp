/*
 * @lc app=leetcode id=344 lang=cpp
 *
 * [344] Reverse String
 */

// @lc code=start
class Solution {
public:
    void reverseString(vector<char>& s) {
        int l = 0, r = s.size() - 1;
        char t; // used for swap
        while(l < r){
            t = s.at(l);
            s.at(l) = s.at(r);
            s.at(r) = t;
            l++;
            r--;
        }
        
    }
};
// @lc code=end

