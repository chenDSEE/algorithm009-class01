/* DP Version */
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        // dp_status[n][0] -> sum of not to rob
        // dp_status[n][1] -> sum of robbing
        vector<vector<int>> dp_status(nums.size(), vector<int> (2, 0));
        dp_status[0][0] = 0, dp_status[0][1] = nums[0];

        for (int who = 1; who < nums.size(); who++) {
            /**
             * 同时存储每一层偷或不偷所能够得到的金额。
             * 在生成这一层偷或不偷的金额的时候，需要根据具体的动作，决定选取 dp_status[who][0] 还是 dp_status[who][1]
             *
             * 跟分治不一样，不是根据上一层偷或不偷来决定这一层怎么做，
             * 而是每一层都作出 偷 或 不偷 两个行为，并记录下来，之后再决定选择哪个历史来进行 sum 的计算
             */
            dp_status[who][0] = max(dp_status[who - 1][0], dp_status[who - 1][1]);
            dp_status[who][1] = dp_status[who - 1][0] + nums[who];
        }

        return max(dp_status[dp_status.size() - 1][0], dp_status[dp_status.size() - 1][1]);
    }
};