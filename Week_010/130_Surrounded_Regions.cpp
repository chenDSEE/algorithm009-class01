// BFS version


// DFS version
class Solution {
private:
    int row;
    int col;
    int move[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    void solve(vector<vector<char>>& board) {
        if (board.size() == 0)
            return ;

        row = board.size();
        col = board[0].size();

        // marking bloder regions
        for (int cnt = 0; cnt < col; cnt++) {
            DFS_marking(board, '#', 0, cnt);
            DFS_marking(board, '#', row - 1, cnt);
        }

        for (int cnt = 0; cnt < row; cnt++) {
            DFS_marking(board, '#', cnt, 0);
            DFS_marking(board, '#', cnt, col - 1);
        }

        // mark 'X' for 'O', '#' for 
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                if (board[x][y] == 'O') {
                    DFS_marking(board, 'X', x, y);
                    // board[x][y] = 'X'; will have worse runtime !!!
                    // 这种方案会降低 CPU 对于 if 的 case 的预测的命中率
                    // DFS 会一次性全部 mark 掉一整块，所以 if 的预测，命中率提高了

                } else if (board[x][y] == '#') {
                    board[x][y] = 'O';
                }
            }
        }
        
    }
    
    void DFS_marking(vector<vector<char>> &board, char mark, int x, int y) {
        if (x < 0 || x > row -1 || y < 0 || y > col - 1 || board[x][y] != 'O') {
            return ;
        }

        board[x][y] = mark;
        for (int step = 0; step < 4; step++) {
            DFS_marking(board, mark, x + move[step][0], y + move[step][1]);
        }
    }
};



// DSU version
class DSU {
private:
    int *parent;
    int *sub_num;

public:
    DSU(const int n) {
        parent = new int[n];
        sub_num = new int[n];
        for (int i = 0; i < n; i++) {
            sub_num[i] = 1;
            parent[i] = i;
        }
    }

    ~DSU() {
        delete [] parent;
        delete [] sub_num;
    }

    bool is_connected(int one, int two) {
        int root_one = find_final_parent(one);
        int root_two = find_final_parent(two);
    
        return root_one == root_two;
    }

    void merge_up(int one, int two) {
        int root_one = find_final_parent(one);
        int root_two = find_final_parent(two);
        if (root_one == root_two)
            return ;

        // 虽然子树做起来也是可以的，但是寻找 root 的时候速度上会有些碍事
        // 因为你每一个新的节点都是挂在 virtual point 上面的
        // 但是并查集的特性，最后跟 virtual point 有关的都会在一个集合里面，
        // 即使根节点不是 virtual point 也没有关系，因为他们始终是 connected 的
        if (sub_num[root_one] > sub_num[root_two]) {
            parent[root_two] = root_one;
            sub_num[root_one] += sub_num[root_two];

        } else {
            parent[root_one] = root_two;
            sub_num[root_two] += sub_num[root_one];
        }
    }

    int find_final_parent(int me) {
        while (me != parent[me]) {
            parent[me] = parent[parent[me]];
            me = parent[me];
        }

        return me;
    }

};

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.size() == 0)
            return ;

        int row = board.size(), col = board[0].size();
        DSU round_set(row * col + 1);   // last one as virtual node for the bloder 'O'
        int virtual_node = row * col;

        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                if (board[x][y] == 'O') {
                    // 边界要跟虚拟节点相连（但是虚拟节点要把它自己身边的节点也检查一次）
                    if (x == 0 || x == row - 1 || y == 0 || y == col - 1) {
                        round_set.merge_up(x * col + y, virtual_node);
                    }

                    if (x < row - 1 && board[x + 1][y] == 'O') {
                        round_set.merge_up(x * col + y, (x + 1) * col + y);
                    }
                    if (y < col - 1 && board[x][y + 1] == 'O') {
                        round_set.merge_up(x * col + y, x * col + y + 1);
                    }
                }
            }
        }

        // rewrite board, you have to do this in here.
        // the 'O' in last row will influence the node upper !!!
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                if (round_set.is_connected(x *col + y, virtual_node)) {
                    board[x][y] = 'O';
                }
            }
        }

        return ;
    }
};