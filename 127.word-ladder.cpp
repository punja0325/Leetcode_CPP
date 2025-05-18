/*
 * @lc app=leetcode id=127 lang=cpp
 *
 * [127] Word Ladder
 *
 * https://leetcode.com/problems/word-ladder/description/
 *
 * algorithms
 * Hard (41.45%)
 * Likes:    12668
 * Dislikes: 1923
 * Total Accepted:    1.3M
 * Total Submissions: 3.1M
 * Testcase Example:  '"hit"\n"cog"\n["hot","dot","dog","lot","log","cog"]'
 *
 * A transformation sequence from word beginWord to word endWord using a
 * dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... ->
 * sk such that:
 * 
 * 
 * Every adjacent pair of words differs by a single letter.
 * Every si for 1 <= i <= k is in wordList. Note that beginWord does not need
 * to be in wordList.
 * sk == endWord
 * 
 * 
 * Given two words, beginWord and endWord, and a dictionary wordList, return
 * the number of words in the shortest transformation sequence from beginWord
 * to endWord, or 0 if no such sequence exists.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log","cog"]
 * Output: 5
 * Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot"
 * -> "dog" -> cog", which is 5 words long.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log"]
 * Output: 0
 * Explanation: The endWord "cog" is not in wordList, therefore there is no
 * valid transformation sequence.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= beginWord.length <= 10
 * endWord.length == beginWord.length
 * 1 <= wordList.length <= 5000
 * wordList[i].length == beginWord.length
 * beginWord, endWord, and wordList[i] consist of lowercase English
 * letters.
 * beginWord != endWord
 * All the words in wordList are unique.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordList_set(wordList.begin(), wordList.end());
        if (wordList_set.find(endWord) == wordList_set.end()) return 0;
        queue<pair<string, int>>q;
        q.push({beginWord, 1});
        while(!q.empty()) {
            auto [s, step] = q.front(); q.pop();
            if (s == endWord) return step;
            for(int i = 0; i < s.size(); i++) {
                char original = s[i];
                for(char c = 'a'; c <= 'z'; c++) {
                    if (c == original) continue;
                    s[i] = c;
                    if (wordList_set.find(s) != wordList_set.end()) {
                        q.push({s, step+1});
                        wordList_set.erase(s);
                    }
                }
                s[i] = original;
            }
        }
        return 0;
    }
};
// @lc code=end

