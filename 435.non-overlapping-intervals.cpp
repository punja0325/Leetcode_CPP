/*
 * @lc app=leetcode id=435 lang=cpp
 *
 * [435] Non-overlapping Intervals
 *
 * https://leetcode.com/problems/non-overlapping-intervals/description/
 *
 * algorithms
 * Medium (53.18%)
 * Likes:    8709
 * Dislikes: 240
 * Total Accepted:    810.5K
 * Total Submissions: 1.5M
 * Testcase Example:  '[[1,2],[2,3],[3,4],[1,3]]'
 *
 * Given an array of intervals intervals where intervals[i] = [starti, endi],
 * return the minimum number of intervals you need to remove to make the rest
 * of the intervals non-overlapping.
 *
 * Note that intervals which only touch at a point are non-overlapping. For
 * example, [1, 2] and [2, 3] are non-overlapping.
 *
 *
 * Example 1:
 *
 *
 * Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
 * Output: 1
 * Explanation: [1,3] can be removed and the rest of the intervals are
 * non-overlapping.
 *
 *
 * Example 2:
 *
 *
 * Input: intervals = [[1,2],[1,2],[1,2]]
 * Output: 2
 * Explanation: You need to remove two [1,2] to make the rest of the intervals
 * non-overlapping.
 *
 *
 * Example 3:
 *
 *
 * Input: intervals = [[1,2],[2,3]]
 * Output: 0
 * Explanation: You don't need to remove any of the intervals since they're
 * already non-overlapping.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= intervals.length <= 10^5
 * intervals[i].length == 2
 * -5 * 10^4 <= starti < endi <= 5 * 10^4
 *
 *
 */

// @lc code=start
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        // Sort intervals by end time
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int count = 1; //count of non-overlapping intervals
        int end = intervals[0][1];

        for(int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= end) {
                //No overlap, we can include this interval
                count++;
                end = intervals[i][1];
            }
            //Else, it's overlapping -> we skip it
        }
        //Total to remove = total - max non-overlapping
        return intervals.size() - count;
    }
};
// @lc code=end

