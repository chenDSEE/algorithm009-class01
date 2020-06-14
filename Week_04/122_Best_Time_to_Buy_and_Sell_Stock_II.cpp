class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int total = 0;
        for (int day = 0; day < prices.size() - 1; day++) {
            if (prices[day] < prices[day + 1])
                total += prices[day + 1] - prices[day]; 
                // 既然长期持有也是赚钱，短期持有也是赚钱，还不如每天都买卖，每天锁定利润
        }

        return total;
    }
};