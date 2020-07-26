/* DP Version 一维数组 */
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        // 每一个 dp_status 都记录当前节点能获得的最大收益 -> 抢这个点
        //                                                -> 不抢
        // curr_pd 就是当前节点，dp_status[curr_dp] 当前节点能获得的最大收益
        // 当前节点不抢的话，收益因该是：dp_status[curr_dp - 1]
        // ==> 那样，上一个节点 curr_dp - 1 不抢的话就是 dp_status[curr_dp - 2]
        // 抢的话：nums[who] + dp_status[curr_dp - 2] 本节点 + 不抢上一个节点的收益
        // 
        // 当前节点不抢，那样当前节点的收益就是上一个节点的收益
        vector<int> dp_status(nums.size() + 1, 0);  // 增加一个节点辅助计算
        dp_status[0] = 0, dp_status[1] = nums[0];
        for (int curr_dp = 2; curr_dp < dp_status.size(); curr_dp++) {
            int who = curr_dp - 1;
            dp_status[curr_dp] = max(dp_status[curr_dp - 1], nums[who] + dp_status[curr_dp - 2]);
        }

        int size = dp_status.size() - 1;
        return max(dp_status[size], dp_status[size - 1]);
    }
};

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        // 每一个 dp_status 都记录当前节点能获得的最大收益 -> 抢这个点
        //                                                -> 不抢
        // curr_pd 就是当前节点，dp_status[curr_dp] 当前节点能获得的最大收益
        // 当前节点不抢的话，收益因该是：dp_status[curr_dp - 1]
        // ==> 那样，上一个节点 curr_dp - 1 不抢的话就是 dp_status[curr_dp - 2]
        // 抢的话：nums[who] + dp_status[curr_dp - 2] 本节点 + 不抢上一个节点的收益
        // 
        // 当前节点不抢，那样当前节点的收益就是上一个节点的收益
        vector<int> dp_status(nums.size() + 2, 0);  // 增加 两个 节点辅助计算
        for (int curr_dp = 2; curr_dp < dp_status.size(); curr_dp++) {
            int who = curr_dp - 2;
            dp_status[curr_dp] = max(dp_status[curr_dp - 1], nums[who] + dp_status[curr_dp - 2]);
        }

        int size = dp_status.size() - 1;
        return max(dp_status[size], dp_status[size - 1]);
    }
};


/* DP Version 二维数组 */
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
             * 而是每一层都作出 偷 或 不偷 两个行为，并记录下两个行为中可以产生的最大收益是多少，之后再决定选择哪个历史来进行 sum 的计算
             */
            dp_status[who][0] = max(dp_status[who - 1][0], dp_status[who - 1][1]);
            dp_status[who][1] = dp_status[who - 1][0] + nums[who];
        }

        return max(dp_status[dp_status.size() - 1][0], dp_status[dp_status.size() - 1][1]);
    }
};

// 内存优化
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        int rob_sum = 0;
        int not_sum = 0;
        for (int who = 0; who < nums.size(); who++) {
            int prev_rob = rob_sum, prev_not = not_sum;
            rob_sum = prev_not + nums[who];
            not_sum = max(prev_rob, prev_not);
        }

        return max(rob_sum, not_sum);
    }
};


class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        int first_sum = 0, second_sum = nums[0], curr_sum;
        for (int who = 1; who < nums.size(); who++) {
            curr_sum = max(second_sum, nums[who] + first_sum);
            first_sum = second_sum;
            second_sum = curr_sum;
        }

        return max(first_sum, second_sum);
    }
};

