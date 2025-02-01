/*
 * @lc app=leetcode id=215 lang=cpp
 *
 * [215] Kth Largest Element in an Array
 *
 * https://leetcode.com/problems/kth-largest-element-in-an-array/description/
 *
 * algorithms
 * Medium (67.45%)
 * Likes:    17595
 * Dislikes: 919
 * Total Accepted:    2.8M
 * Total Submissions: 4.1M
 * Testcase Example:  '[3,2,1,5,6,4]\n2'
 *
 * Given an integer array nums and an integer k, return the k^th largest
 * element in the array.
 * 
 * Note that it is the k^th largest element in the sorted order, not the k^th
 * distinct element.
 * 
 * Can you solve it without sorting?
 * 
 * 
 * Example 1:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 * Example 2:
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 
 * 
 */

// @lc code=start
//#define SORTING
#define PRIORITY_QUEUE
//#define QUICK_SELECT // I don't understand this one
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        #ifdef SORTING
        sort(nums.begin(), nums.end(), customCompare);
        return nums[k-1];
        #endif
        #ifdef PRIORITY_QUEUE
        priority_queue<int, vector<int>, greater<int>> pq; // 小頂堆(minHeap)
        //priority_queue<int> pq;
        
        for (int num : nums) {
            pq.push(num);
            if (pq.size() > k) {
                pq.pop(); // 保持堆的大小為 k
            }
        }
        return pq.top(); // 堆頂就是第 K 大的數字
        #endif
        #ifdef QUICK_SELECT
        #endif

    }
#ifdef SORTING
private:
    static bool customCompare(int a, int b) {
        return a > b;
    }
#endif
};
// @lc code=end

