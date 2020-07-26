/* 压缩状态 DP */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        int prev_not = 0, prev_has = -prices[0];
        for (int day = 1; day < prices.size(); day++) {
            // use prev data update today into prev_has, prev_not
            prev_not = max(prev_not, prev_has + prices[day]);
            prev_has = max(prev_has, -prices[day]);
        }

        return prev_not;
    }
};


/* DP Version */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        vector<vector<int>> dp_status(prices.size(), vector<int>(2, 0));
        dp_status[0][0] = 0;
        dp_status[0][1] = -prices[0];

        for (int day = 1; day < prices.size(); day++) {
            dp_status[day][0] = max(dp_status[day - 1][0], dp_status[day - 1][1] + prices[day]);
            // 现在的总收益（持有状态下） = max（以昨天的价格ci'you持有，今天才买进）
            // 由于只能交易一次，但是我又要假设我是今天才买进的，所以 "-prices[day]" 跟 "dp_status[0][1] = -prices[0];" 类似
            // 你要是用 "dp_status[day - 1][0] - prices[day]" 那就是新的一次交易了，控制买入次数 跟 控制卖出次数是一样的

            // 另一种解释可以是这样
            // dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
            // dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i]) 
            //             = max(dp[i-1][1][1], -prices[i])
            // 解释：k = 0 的 base case，所以 dp[i-1][0][0] = 0。
            // 
            // 现在发现 k 都是 1，不会改变，即 k 对状态转移已经没有影响了。
            // 可以进行进一步化简去掉所有 k：
            // dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
            // dp[i][1] = max(dp[i-1][1], -prices[i])
            dp_status[day][1] = max(dp_status[day - 1][1], -prices[day]);   // 而且这里具有：看看今天的买入价格是不是可以做到更低 的效果
        }

        // return max(dp_status[prices.size() - 1][0], dp_status[prices.size() - 1][1]);
        // 最后一天还持有，账面上肯定是亏损的
        return dp_status[prices.size() - 1][0];
    }
};




// 找到最小值，计算价格差
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        int min_val = INT_MAX;
        int max_sum = 0;

        // 实际上这不仅仅是做了一次交易
        // 而是不断尝试新一天的价格 - 当前遇到过的最小值，看看能不能刷新 max_sum
        // max_sum 实际上是被不断增量更新出来的
        for (int curr : prices) {
            min_val = curr < min_val ? curr : min_val;
            max_sum = max_sum < (curr - min_val) ? curr - min_val : max_sum;
        }

        return max_sum;
    }
};