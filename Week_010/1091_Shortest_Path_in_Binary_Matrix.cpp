int row, col;

class serach_node {
public:
    serach_node(int _x, int _y, int _src_step)
        : x(_x), y(_y), src_step(_src_step) {}

    int x;
    int y;
    int src_step;

};

bool operator < (const serach_node &one, const serach_node &two) {
    return max(row - 1 - one.x, col - 1 - one.y) + one.src_step >= max(row - 1 - two.x, col - 1 - two.y) + two.src_step;
}

class Solution {
private:
    vector<vector<int>> move_pos = {{-1, -1}, {0, -1}, {1, -1},
                                    {-1,  0},          {1, 0},
                                    {-1,  1}, {0,  1}, {1, 1}};

public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if (grid.size() == 0)
            return -1;
        
        row = grid.size(), col = grid[0].size();
        if (row == 1 && col == 1)
            return 1;

        if (grid[0][0] == 1 || grid[row - 1][col - 1] == 1)
            return -1;

        priority_queue<serach_node> p_queue;

        p_queue.push(serach_node{0, 0, 1});
        vector<int> step_record(row * col, 0);
        step_record[0] = 1;

        while (!p_queue.empty()) {
            serach_node curr_node = p_queue.top();
            p_queue.pop();
            int curr_index = curr_node.x * col + curr_node.y;
            grid[curr_node.x][curr_node.y] = 1; // 防止返回，直接堵上。由于 p_queue 是全部都有可能放进来的
            for (int i = 0; i < move_pos.size(); i++) {
                int next_x = curr_node.x + move_pos[i][0];
                int next_y = curr_node.y + move_pos[i][1];
                int next_index = next_x * col + next_y;
                if (next_x >= 0 && next_x < row && next_y >= 0 && next_y < col && grid[next_x][next_y] == 0) {
                    if (next_x == row - 1 && next_y == col -1) {
                        return step_record[curr_index] + 1;
                    }

                    // next node 没去过 || next node 已经去过，但是从 curr node 去 next node 比其之前去 next onde 的方案更短
                    if (step_record[next_index] == 0 || step_record[next_index] > step_record[curr_index] + 1) {
                        step_record[next_index] = step_record[curr_index] + 1;
                        p_queue.push(serach_node {next_x, next_y, step_record[next_index]});
                    }
                }
            }
        } // end of while

        return -1;
    }
};


/* crazy version for A* search */
int row, col;

class serach_node {
public:
    serach_node(int _x, int _y, int _src_step)
        : x(_x), y(_y), src_step(_src_step) {}

    int x;
    int y;
    int src_step;
};


struct cmp
{
    bool operator() (serach_node *one, serach_node *two)
    {
        return max(row - 1 - one->x, col - 1 - one->y) + one->src_step >= max(row - 1 - two->x, col - 1 - two->y) + two->src_step;
    }
};

class Solution {
private:
    vector<vector<int>> move_pos = {{-1, -1}, {0, -1}, {1, -1},
                                    {-1,  0},          {1, 0},
                                    {-1,  1}, {0,  1}, {1, 1}};

public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if (grid.size() == 0)
            return -1;
        
        row = grid.size(), col = grid[0].size();
        if (row == 1 && col == 1)
            return 1;

        if (grid[0][0] == 1 || grid[row - 1][col - 1] == 1)
            return -1;

        vector<serach_node> step_record(row * col, {0, 0, 0});
        step_record[0] = {0, 0, 1};

        priority_queue<serach_node *, vector<serach_node *>, cmp> p_queue;
        p_queue.push(&step_record[0]);

        while (!p_queue.empty()) {
            serach_node *curr_node = p_queue.top();
            p_queue.pop();
            int curr_index = curr_node->x * col + curr_node->y;
            grid[curr_node->x][curr_node->y] = 1; // 防止返回，直接堵上。由于 p_queue 是全部都有可能放进来的

            for (int i = 0; i < move_pos.size(); i++) {
                int next_x = curr_node->x + move_pos[i][0];
                int next_y = curr_node->y + move_pos[i][1];
                int next_index = next_x * col + next_y;
                if (next_x >= 0 && next_x < row && next_y >= 0 && next_y < col && grid[next_x][next_y] == 0) {
                    if (next_x == row - 1 && next_y == col -1) {
                        return step_record[curr_index].src_step + 1;
                    }

                    // next node 没去过 || next node 已经去过，但是从 curr node 去 next node 比其之前去 next onde 的方案更短
                    if (step_record[next_index].src_step == 0 
                        || step_record[next_index].src_step > step_record[curr_index].src_step + 1) 
                    {
                        step_record[next_index].x = next_x;
                        step_record[next_index].y = next_y;
                        step_record[next_index].src_step = step_record[curr_index].src_step + 1;
                        p_queue.push(&step_record[next_index]);
                    }
                }
            }
        } // end of while

        return -1;
    }
};
