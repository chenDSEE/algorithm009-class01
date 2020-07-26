/* 状态压缩 DP */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        int prev_not = 0, prev_has = -prices[0];
        for (int day = 1; day < prices.size(); day++) {
            prev_not = max(prev_not, prev_has + prices[day]);
            prev_has = max(prev_has, prev_not - prices[day]);
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

        vector<vector<int>> dp_status(prices.size(), vector<int> (2, 0));
        dp_status[0][0] = 0;
        dp_status[0][1] = -prices[0];

        for (int day = 1; day < prices.size(); day++) {
            dp_status[day][0] = max(dp_status[day - 1][0], dp_status[day - 1][1] + prices[day]);
            dp_status[day][1] = max(dp_status[day - 1][1], dp_status[day - 1][0] - prices[day]);
        }

        return dp_status[prices.size() - 1][0];
    }
};


// 一次遍历
// 虽然题目要求不能同一天进行交易，但是实际上对于程序来说是没有关系的
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        int sum = 0;
        for (int day = 1; day < prices.size(); day++) {
            if (prices[day] > prices[day - 1]) {
                sum += prices[day] - prices[day - 1];
                // 既然长期持有也是赚钱，短期持有也是赚钱，还不如每天都买卖，每天锁定利润
            }
        }

        return sum;
    }
};