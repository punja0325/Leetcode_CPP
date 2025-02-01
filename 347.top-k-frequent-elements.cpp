/*
 * @lc app=leetcode id=347 lang=cpp
 *
 * [347] Top K Frequent Elements
 *
 * https://leetcode.com/problems/top-k-frequent-elements/description/
 *
 * algorithms
 * Medium (63.89%)
 * Likes:    17930
 * Dislikes: 693
 * Total Accepted:    2.6M
 * Total Submissions: 4M
 * Testcase Example:  '[1,1,1,2,2,3]\n2'
 *
 * Given an integer array nums and an integer k, return the k most frequent
 * elements. You may return the answer in any order.
 * 
 * 
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * k is in the range [1, the number of unique elements in the array].
 * It is guaranteed that the answer is unique.
 * 
 * 
 * 
 * Follow up: Your algorithm's time complexity must be better than O(n log n),
 * where n is the array's size.
 * 
 */

// @lc code=start
#define PRIORITY_QUEUE
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        #ifdef PRIORITY_QUEUE
        // Count the frequency of each element
        unordered_map<int, int> frequencyMap;
        for (int num : nums) {
            frequencyMap[num]++;
        }

        // Create a priority queue
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        for (auto pair : frequencyMap) {
            pq.push({pair.second, pair.first});
            if (pq.size() > k) {
                pq.pop(); // pop the smallest element
            }
        }
        // Get the top k elements
        vector<int> topK;
        while (!pq.empty()) {
            topK.push_back(pq.top().second);
            pq.pop();
        }
        return topK;
        #endif
    }
};
// @lc code=end

