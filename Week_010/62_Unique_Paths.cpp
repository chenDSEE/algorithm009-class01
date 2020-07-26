// 从起点开始出发，走到当前格子有多少种走法？ 走法 = 上面的 + 左边的 （因为要走到当前格子，只能够从这两个地方来）
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp_status(n, vector<int>(m));

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                if (row == 0 || col == 0) {
                    dp_status[row][col] = 1;
                
                } else {
                    dp_status[row][col] = dp_status[row - 1][col] + dp_status[row][col - 1];
                }
            }
        }

        return dp_status[n - 1][m - 1];
    }
};

// 从当前格子出发，走到终点各自有多少种走法？ 走法 = 下面的 + 右边的 （因为要走到终点格子，只能够向这两个地方走）
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp_status(n, vector<int>(m));

        for (int row = n - 1; row >= 0; row--) {
            for (int col = m - 1; col >= 0; col--) {
                if (row == n - 1 || col == m -1) {
                    dp_status[row][col] = 1;
                
                } else {
                    dp_status[row][col] = dp_status[row + 1][col] + dp_status[row][col + 1];
                }
            }
        }

        return dp_status[0][0];
    }
};

// better version for dynamic programming
// Further inspecting the above code, pre[j] is just the cur[j] before the update. 
// So we can further reduce the memory usage to one row.
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp_status(n, 1);

        for (int row = 1; row < m; row++) {
            for (int col = 1; col < n; col++) {
                dp_status[col] += dp_status[col - 1];   // curr_level_status = last_level_status + left_status
            }
        }

        return dp_status[n - 1];
    }
};



