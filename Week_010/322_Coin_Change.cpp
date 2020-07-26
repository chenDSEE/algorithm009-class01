// BFS

// 贪心

// DFS + 记忆化



// DP version
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp_status[index]: 当金额为 index 的时候，最少要多少个硬币？
        // dp_status[index]，在同一个 金额 index 下是在不停更新的，因为你有很多种尝试的方案嘛
        //
        // 个数加一是为了最大那个 index 是 amount，内容初始化为 amount + 1 是确保当采用全部 1 coin 的方案时能够被更新，
        // 同时，能够看出 dp_status[amount] 能不能被这些零钱调配出来
        vector<int> dp_status(amount + 1, amount + 1);

        dp_status[0] = 0;
        for (int curr_sum = 1; curr_sum <= amount; curr_sum++) {
            for (int type = 0; type < coins.size(); type++) {
                if (coins[type] <= curr_sum) {
                    // 究竟才不采用这个 coins[type] 就取决于那个用的硬币数量少
                    dp_status[curr_sum] = min(dp_status[curr_sum], dp_status[curr_sum - coins[type]] + 1);
                }
            }
        }

        // 看一下 dp_status[amount] 能不能被这些零钱调配出来
        return dp_status[amount] > amount ? -1 : dp_status[amount];
    }
};