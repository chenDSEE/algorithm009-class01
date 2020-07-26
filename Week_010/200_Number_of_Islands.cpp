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

// Disjoint Set Union version(DSU)
class union_set {
private:
    int  num;
    int *parent;

public:
    union_set(int n) : num(n) {
        parent = new int[n];
        for (int i = 0; i < num; i++) {
            parent[i] = i;
        }
    }

    ~union_set() {
        delete [] parent;
    }

    int find_fin_parent(int me) {
        while (me != parent[me]) {
            parent[me] = parent[parent[me]];
            me = parent[me];
        }

        return me;
    }

    void merge_up(int one, int two) {
        int root_one = find_fin_parent(one);
        int root_two = find_fin_parent(two);
        if (root_one == root_two)
            return ;

        parent[root_two] = root_one;
        num--;
    }

    int get_num() {
        return num;
    }
    
    void adjust() {
        num--;
    }
};


class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() == 0)
            return 0;

        int X = grid.size(), Y = grid[0].size();
        union_set island_set(X * Y);

        for (int x = 0; x < X; x++) {
            for (int y = 0; y < Y; y++) {
                if (grid[x][y] == '0') {
                    island_set.adjust();
                } else {
                    if (y < Y - 1 && grid[x][y + 1] == '1')
                        island_set.merge_up(x * Y + y, x * Y + y + 1);
                    if (x < X - 1 && grid[x + 1][y] == '1')
                        island_set.merge_up(x * Y + y, (x + 1) * Y + y);
                }
            }
        }

        return island_set.get_num();
    }
};