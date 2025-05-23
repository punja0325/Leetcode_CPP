/*
 * @lc app=leetcode id=56 lang=cpp
 *
 * [56] Merge Intervals
 *
 * https://leetcode.com/problems/merge-intervals/description/
 *
 * algorithms
 * Medium (48.58%)
 * Likes:    23175
 * Dislikes: 836
 * Total Accepted:    3.1M
 * Total Submissions: 6.2M
 * Testcase Example:  '[[1,3],[2,6],[8,10],[15,18]]'
 *
 * Given an array of intervals where intervals[i] = [starti, endi], merge all
 * overlapping intervals, and return an array of the non-overlapping intervals
 * that cover all the intervals in the input.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlap, merge them into
 * [1,6].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: intervals = [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= intervals.length <= 10^4
 * intervals[i].length == 2
 * 0 <= starti <= endi <= 10^4
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> merged;
        //Sort interval by start time
        sort(intervals.begin(), intervals.end());
        merged.push_back(intervals[0]);
        //Merge interval
        for(const auto& interval : intervals) {
            if (merged.back()[1] >= interval[0]) {
                //Overlapping, merge thme
                merged.back()[1] = max(merged.back()[1], interval[1]);
            } else {
                //Non-overlapping, push new interval
                merged.push_back(interval);
            }
        }
        return merged;
    }
};
// @lc code=end

