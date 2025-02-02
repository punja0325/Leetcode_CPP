void backtrack(參數) {
    if (滿足條件) {  // 終止條件
        將結果加入解集中
        return
    }
    for (每一個可能的選擇) {  // 嘗試所有可能性
        做出選擇
        backtrack(下一個狀態)  // 繼續探索
        撤銷選擇  // 回溯
    }
}

void backtrack(int start) {
    if (termination condition) {  // Check if the condition is met
        add the result to the solution set
        return
    }
    for (each possible choice) {  // Try all possible options
        make a choice
        backtrack(next state)  // Proceed to the next step
        undo the choice  // Backtrack
    }
}

// Leetcode 46:
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        /*
        - Use backtracking to generate all permutations.
        - Swap elements to explore all possible arrangements.
        - Use a start index to track the current position in the array.
        */
        vector<vector<int>> res;
        backtrack(nums, 0, res); // Start backtracking from index 0
        return res;
    }
private:
    void backtrack(vector<int>& nums, int start, vector<vector<int>>& res) {
        // If we've reached the end of the array, add the current permutation to the result
        if (start == nums.size()) {
            res.push_back(nums);
            return;
        }

        // Explore all possible permutations by swapping elements
        for(int i = start; i < nums.size(); i++) {
            swap(nums[start], nums[i]);
            backtrack(nums, start + 1,  res); // Recurse on the next position
            swap(nums[start], nums[i]); // Backtrack: undo the swap
        }
    }

};
// Leetcode 77:
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> temp;
        if (k < 0 || k > n) return res; // 返回空结果，如果k不在有效范围内
        backtrack(n, k, 0, temp, res);
        return res;
    }
private:
    void backtrack(int n, int k, int start, vector<int>& temp, vector<vector<int>>& res) {
        // 終止條件：當當前路径的長度等於k，將其添加到結果中
        if (temp.size() == k) {
            res.push_back(temp);
            return;
        }

        // 從start+1開始選擇下一個元素，避免重復
        for (int i = start + 1; i <= n; ++i) {
            temp.push_back(i); // 選擇i
            backtrack(n, k, i, temp, res); // 遞歸，繼續選擇下一個元素
            temp.pop_back(); // 撤銷選擇，回溯
        }
    }
};


