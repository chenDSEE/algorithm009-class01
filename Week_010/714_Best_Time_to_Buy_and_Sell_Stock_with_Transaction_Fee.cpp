/* 状态压缩 DP */
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        if (prices.size() == 0) {
            return 0;
        }

        // dp_status[day][has?]
        int prev_not = 0, prev_has = -prices[0] - fee;
        for (int day = 0; day < prices.size(); day++) {
            int temp = prev_not;	// 这个很重要！！不然很有可能出错，哪怕 Leetcode 上面能够 AC
            prev_not = max(prev_not, prev_has + prices[day]);
            prev_has = max(prev_has, temp - prices[day] - fee);
        }

        return prev_not;
    }
};



/* DP Version */
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        if (prices.size() == 0) {
            return 0;
        }

        // dp_status[day][has?]
        vector<vector<int>> dp_status(prices.size(), vector<int>(2, 0));
        dp_status[0][0] = 0;
        dp_status[0][1] = -prices[0] - fee;

        for (int day = 1; day < prices.size(); day++) {
            dp_status[day][0] = max(dp_status[day - 1][0], dp_status[day - 1][1] + prices[day]);
            dp_status[day][1] = max(dp_status[day - 1][1], dp_status[day - 1][0] - prices[day] - fee);
        }


        return dp_status[prices.size() - 1][0];
    }
};