/* 状态压缩 DP */
// 基本不考



// DP 代码简化版本
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.size() == 0 || k <= 0) {
            return 0;
        }

        // k > (day / 2)  ==> k 就是无数次交易
        if (k >= (prices.size() >> 1)) {
            return greedy(prices);
        }

        // dp_status[day][cnt][has?]
        vector<vector<vector<int>>> dp_status(prices.size(), vector<vector<int>> (k + 1, vector<int> (2, 0)));

        // DP
        for (int day = 0; day < prices.size(); day++) {
            for (int cnt = 0; cnt <= k; cnt++) {
                if (day == 0) {
                    dp_status[day][cnt][0] = 0;
                    dp_status[day][cnt][1] = -prices[0];
                    continue;
                }

                if (cnt != 0)
                    dp_status[day][cnt][0] = max(dp_status[day - 1][cnt][0], dp_status[day - 1][cnt - 1][1] + prices[day]);

                dp_status[day][cnt][1] = max(dp_status[day - 1][cnt][1], dp_status[day - 1][cnt][0] - prices[day]);
            }
        }

        // get the best one in last day
		// 毕竟是每交易一次，就赚一次的钱，那当然是尽可能交易啊
		// 而且，每一个 dp_status 都是能够包含所有前面子问题中的最优解的，所以直接看 k 次交易也是完全不虚的
        return dp_status[prices.size() - 1][k][0];
    }

private:
    int greedy(const vector<int> &prices) {
        int max_sum = 0;
        for (int day = 1; day < prices.size(); day++) {
            if (prices[day] > prices[day - 1]) {
                max_sum += prices[day] - prices[day - 1];
            }
        }

        return max_sum;
    }
};



// DP 最原始版本
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.size() == 0 || k <= 0) {
            return 0;
        }

        // k > (day / 2)  ==> k 就是无数次交易
		// 209/211 cases passed
        if (k >= (prices.size() >> 1)) {
            return greedy(prices);
        }


        // dp_status[day][cnt][has?]
        vector<vector<vector<int>>> dp_status(prices.size(), vector<vector<int>> (k + 1, vector<int> (2, 0)));
/*
		也可以
        int dp_status[prices.size()][k + 1][2];
        memset(dp_status, 0, sizeof(dp_status));
*/

        // init dp_status
        // 解释：
        //   dp[i][0] 
        // = max(dp[-1][0], dp[-1][1] + prices[i])
        // = max(0, -infinity + prices[i]) = 0
        // dp[i][1] = -prices[i];
        //解释：
        //   dp[i][1] 
        // = max(dp[-1][1], dp[-1][0] - prices[i])
        // = max(-infinity, 0 - prices[i]) 
        // = -prices[i]        。
		for (int cnt = 0; cnt <= k; cnt++) {
            // 第 1 天买入 - 卖出循环 K 次之后不再买入，所以初始值为 0
            dp_status[0][cnt][0] = 0;
            // 第 1 天买入 - 卖出循环 K 次之后又买入，所以初始值为 -prices[0]
            dp_status[0][cnt][1] = -prices[0];
        }

        // DP
        for (int day = 1; day < prices.size(); day++) {
            for (int cnt = 0; cnt <= k; cnt++) {
				// 不想这样处理的话，就用 for (int k = max_k; k >= 1; k--) 反过来
                if (cnt != 0)
                    dp_status[day][cnt][0] = max(dp_status[day - 1][cnt][0], dp_status[day - 1][cnt - 1][1] + prices[day]);
                else
                    dp_status[day][cnt][0] = dp_status[day - 1][cnt][0];

                dp_status[day][cnt][1] = max(dp_status[day - 1][cnt][1], dp_status[day - 1][cnt][0] - prices[day]);
            }
        }

        // get the best one in last day
        int max_sum = INT_MIN;
        for (int cnt = 0; cnt <= k; cnt++) {
            max_sum = max(max_sum, dp_status[prices.size() - 1][cnt][0]);
        }

        return max_sum;
    }

private:
    int greedy(const vector<int> &prices) {
        int max_sum = 0;
        for (int day = 1; day < prices.size(); day++) {
            if (prices[day] > prices[day - 1]) {
                max_sum += prices[day] - prices[day - 1];
            }
        }

        return max_sum;
    }

};