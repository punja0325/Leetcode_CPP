/*
 * @lc app=leetcode id=49 lang=cpp
 *
 * [49] Group Anagrams
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagrams;
        //Sort the string and use it as a key in the map
        for (const string &s : strs) {
            string sorted_s = s;
            sort(sorted_s.begin(), sorted_s.end());
            anagrams[sorted_s].push_back(s);
        }
        vector<vector <string>> result;
        for(const auto& p : anagrams) {
            result.push_back(p.second);
        }
        return result;
    }
};
// @lc code=end

