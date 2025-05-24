/*
 * @lc app=leetcode id=451 lang=cpp
 *
 * [451] Sort Characters By Frequency
 *
 * https://leetcode.com/problems/sort-characters-by-frequency/description/
 *
 * algorithms
 * Medium (72.52%)
 * Likes:    8703
 * Dislikes: 311
 * Total Accepted:    904.7K
 * Total Submissions: 1.2M
 * Testcase Example:  '"tree"'
 *
 * Given a string s, sort it in decreasing order based on the frequency of the
 * characters. The frequency of a character is the number of times it appears
 * in the string.
 *
 * Return the sorted string. If there are multiple answers, return any of
 * them.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "tree"
 * Output: "eert"
 * Explanation: 'e' appears twice while 'r' and 't' both appear once.
 * So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid
 * answer.
 *
 *
 * Example 2:
 *
 *
 * Input: s = "cccaaa"
 * Output: "aaaccc"
 * Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and
 * "aaaccc" are valid answers.
 * Note that "cacaca" is incorrect, as the same characters must be together.
 *
 *
 * Example 3:
 *
 *
 * Input: s = "Aabb"
 * Output: "bbAa"
 * Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
 * Note that 'A' and 'a' are treated as two different characters.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 5 * 10^5
 * s consists of uppercase and lowercase English letters and digits.
 *
 *
 */

// @lc code=start
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> FrequenceMap;
        for(char c : s) {
            FrequenceMap[c]++;
        }
        priority_queue<pair<int, char>> pq; // (freq, element)
        for(auto &entry : FrequenceMap) {
            char element = entry.first;
            int freq = entry.second;
            pq.push({freq, element});
        }
        int index = 0;
        while(!pq.empty()) {
            auto [freq, element] = pq.top(); pq.pop();
            for(int i = 0; i < freq; i++) {
                s[index++] = element;
            }
        }
        return s;
    }
};
// @lc code=end

