/* DFS version */
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int land_cnt = 0;
        
        for (int x = 0; x < grid.size(); x++) {
            for (int y = 0; y < grid[x].size(); y++) {
                if (grid[x][y] == '1') {
                    DFS_marking(grid, x, y);
                    land_cnt++;
                }
            }
        }

        return land_cnt;
    }

    void DFS_marking(vector<vector<char>> &grid, const int x, const int y) {
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[x].size())
            return ;
        if (grid[x][y] == '0')
            return ;

        grid[x][y] = '0';
        DFS_marking(grid, x - 1, y);
        DFS_marking(grid, x + 1, y);
        DFS_marking(grid, x, y - 1);
        DFS_marking(grid, x, y + 1);
    }
};

/* BFS version */
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int land_cnt = 0;

        for (int x = 0; x < grid.size(); x++) {
            for (int y = 0; y < grid[x].size(); y++) {
                if (grid[x][y] == '1') {
                    BFS_marking(grid, x, y);
                    land_cnt++;
                }
            }
        }

        return land_cnt;
    }

    void BFS_marking(vector<vector<char>> &grid, const int x, const int y) {


        queue<pair<int, int>> wait_queue; // x -> y
        wait_queue.push({x, y});
        while (!wait_queue.empty()) {
            int x_curr = wait_queue.front().first;
            int y_curr = wait_queue.front().second;
            wait_queue.pop();

            if (x_curr < 0 || x_curr >= grid.size() || y_curr < 0 || y_curr >= grid[x_curr].size())
                continue ;

            if (grid[x_curr][y_curr] == '0')
                continue;

            grid[x_curr][y_curr] = '0';
            wait_queue.push({x_curr + 1, y_curr});
            wait_queue.push({x_curr - 1, y_curr});
            wait_queue.push({x_curr, y_curr + 1});
            wait_queue.push({x_curr, y_curr - 1});
        }   // end of while

        return ;
    }
};