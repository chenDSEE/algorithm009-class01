// 状态压缩 DP version
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        
        // 第一层的时候，确确实实，能累计到的最大值跟最小值就是 nums[0], 你不可能自己填一个数的
        // 你怎么知道你填写的数字在不在 nums 里面呢？
        int max_val = nums[0], min_val = nums[0], answer = nums[0];
        for (int index = 1; index < nums.size(); index++) {
            if (nums[index] < 0) {
                std::swap(max_val, min_val);
            }

            // 计算出当前层的 max_val, 并保留历史上可能造成的 min_val，以备日后遇上一个负数的时候使用
            max_val = std::max(max_val * nums[index], nums[index]);
            min_val = std::min(min_val * nums[index], nums[index]);

            answer = max(answer, max_val);
        }

        return answer;
    }
};

/* DP version */
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        // 0 -> -, 1 -> +
        // 最大，最小 会更合适，而不是正负，因为可能当前累计值中没有 负数 或 正数 的
        // 尤其是在 子数组 的情况下
        vector<vector<int>> dp_status(nums.size(), vector<int> (2, 0));
        dp_status[0][0] = nums[0];
        dp_status[0][1] = nums[0];

        for (int cnt = 1; cnt < nums.size(); cnt++) {
            if (nums[cnt] > 0) {
                // 继承历史遗留，还不如用自己
                dp_status[cnt][0] = min(nums[cnt] * dp_status[cnt - 1][0], nums[cnt]);
                dp_status[cnt][1] = max(nums[cnt] * dp_status[cnt - 1][1], nums[cnt]);

            } else {
                dp_status[cnt][0] = min(nums[cnt] * dp_status[cnt - 1][1], nums[cnt]);
                dp_status[cnt][1] = max(nums[cnt] * dp_status[cnt - 1][0], nums[cnt]);
            }
        }
        
        int max_val = INT_MIN;
        for (int cnt = 0; cnt < nums.size(); cnt++) {
            max_val = max_val < dp_status[cnt][1] ? dp_status[cnt][1] : max_val;
        }

        return max_val;
    }

};