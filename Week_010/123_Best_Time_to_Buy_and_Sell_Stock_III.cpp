/* 状态压缩 DP */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        // 这里你能够压缩掉的实际上只有 day
        // dp_status[cnt][has]
        vector<vector<int>> dp_status(3, vector<int>(2, 0));
        dp_status[0][0] = 0, dp_status[0][1] = -prices[0];
        dp_status[1][0] = 0, dp_status[1][1] = -prices[0];
        dp_status[2][0] = 0, dp_status[2][1] = -prices[0];

        for (int day = 0; day < prices.size(); day++) {
            for (int cnt = 0; cnt < dp_status.size(); cnt++) {
                dp_status[cnt][0] = cnt == 0 ? dp_status[cnt][0] : max(dp_status[cnt][0], dp_status[cnt - 1][1] + prices[day]);
                dp_status[cnt][1] = max(dp_status[cnt][1], dp_status[cnt][0] - prices[day]);
            }
        }

        return dp_status[2][0];
    }
};


/* DP Version */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        vector<vector<vector<int>>> dp_status(prices.size(), vector<vector<int>> (3, vector<int> (2, 0)));
        // 当天买，当天卖
        dp_status[0][0][0] = 0, dp_status[0][0][1] = -prices[0]; 
        dp_status[0][1][0] = 0, dp_status[0][1][1] = -prices[0];
        dp_status[0][2][0] = 0, dp_status[0][2][1] = -prices[0];

        for (int day = 1; day < prices.size(); day++) {
            for (int cnt = 0; cnt < 3; cnt++) {
                // 完备性 !
                dp_status[day][cnt][0] = cnt == 0 ? dp_status[day - 1][cnt][0] : max(dp_status[day - 1][cnt][0], dp_status[day - 1][cnt - 1][1] + prices[day]);
                dp_status[day][cnt][1] = max(dp_status[day - 1][cnt][1], dp_status[day - 1][cnt][0] - prices[day]);
            }
        }

        int max_sum = INT_MIN;
        for (int cnt = 0; cnt < 3; cnt++) {
            max_sum = max_sum < dp_status[prices.size() - 1][cnt][0] ? dp_status[prices.size() - 1][cnt][0] : max_sum;
        }

        return max_sum;
    }
};