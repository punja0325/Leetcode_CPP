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
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if (k <= 0 || nums.empty()) {
            return {};
        }

        // Count the frequency of each element
        unordered_map<int, int> frequencyMap;
        for (int num : nums) {
            frequencyMap[num]++;
        }

        // Create a priority queue to store (frequency, element)
        priority_queue<pair<int, int>> pq; //frequency, element

        // Populate the priority queue
        for (auto& entry : frequencyMap) {
            int element = entry.first;
            int frequency = entry.second;
            pq.push({frequency, element});
        }

        // Extract top k elements
        vector<int> result;
        int count = 0;
        while (!pq.empty() && count < k) {
            result.push_back(pq.top().second);
            pq.pop();
            count++;
        }

        return result;
    }
};
// @lc code=end

