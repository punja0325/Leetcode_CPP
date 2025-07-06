/*
 * @lc app=leetcode id=152 lang=cpp
 *
 * [152] Maximum Product Subarray
 *
 * https://leetcode.com/problems/maximum-product-subarray/description/
 *
 * algorithms
 * Medium (35.06%)
 * Likes:    19397
 * Dislikes: 784
 * Total Accepted:    1.6M
 * Total Submissions: 4.7M
 * Testcase Example:  '[2,3,-2,4]'
 *
 * Given an integer array nums, find a subarray that has the largest product,
 * and return the product.
 *
 * The test cases are generated so that the answer will fit in a 32-bit
 * integer.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [2,3,-2,4]
 * Output: 6
 * Explanation: [2,3] has the largest product 6.
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [-2,0,-1]
 * Output: 0
 * Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 2 * 10^4
 * -10 <= nums[i] <= 10
 * The product of any subarray of nums is guaranteed to fit in a 32-bit
 * integer.
 *
 *
 */

// @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;

        int maxProd = nums[0]; // Current maximum product
        int minProd = nums[0]; // Current minimum product
        int result = nums[0];  // Global maximum product

        for(int i = 1; i < nums.size(); i++) {
            int curr = nums[i];

            //If the current number is negative, swap max and min
            if (curr < 0) {
                swap(maxProd, minProd);
            }

            //Update max and min products ending at current index
            maxProd = max(curr, curr * maxProd);
            minProd = min(curr, curr * minProd);

            //Update global result
            result = max(result, maxProd);
        }
        return result;
    }
};
// @lc code=end

