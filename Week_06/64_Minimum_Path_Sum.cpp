class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp_status = grid[0];

        for (int col = 1; col < n; ++col)
            dp_status[col] += dp_status[col - 1];

        for (int row = 1; row < m; ++row) {
            for (int col = 0; col < n; ++col) {
                if (col == 0) dp_status[col] = dp_status[col] + grid[row][col];
                else dp_status[col] = min(dp_status[col - 1], dp_status[col]) + grid[row][col];
            }
        }
        return dp_status[n - 1];
    }
};
