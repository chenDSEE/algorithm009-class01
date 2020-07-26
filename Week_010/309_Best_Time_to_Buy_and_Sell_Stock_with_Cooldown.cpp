/* 状态压缩 DP */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        int hot_not = 0, hot_has = -prices[0], cold_not = 0;
        for (int day = 1; day < prices.size(); day++) {
            // 自己尝试用画状态机的转换过程，这里的答案就出来了
            int new_hot_not = max(hot_not, cold_not);
            int new_hot_has = max(hot_has, hot_not - prices[day]);
            int new_cold_not = hot_has + prices[day];
            hot_not = new_hot_not;
            hot_has = new_hot_has;
            cold_not = new_cold_not;
        }

        return max(hot_not, cold_not);
    }
};

/* CXX-11 DP Version */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int n = prices.size();
        int f0 = -prices[0];
        int f1 = 0;
        int f2 = 0;
        for (int i = 1; i < n; ++i) {
            tie(f0, f1, f2) = make_tuple(max(f0, f2 - prices[i]), f0 + prices[i], max(f1, f2));
        }

        return max(f1, f2);
    }
};

/* DP Version */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int n = prices.size();
        // f[i][0]: 手上持有股票的最大收益
        // f[i][1]: 手上不持有股票，并且处于冷冻期中的累计最大收益
        // f[i][2]: 手上不持有股票，并且不在冷冻期中的累计最大收益
        vector<vector<int>> f(n, vector<int>(3));
        f[0][0] = -prices[0];
        for (int i = 1; i < n; ++i) {
            f[i][0] = max(f[i - 1][0], f[i - 1][2] - prices[i]);
            f[i][1] = f[i - 1][0] + prices[i];
            f[i][2] = max(f[i - 1][1], f[i - 1][2]);
        }
        return max(f[n - 1][1], f[n - 1][2]);
    }
};
