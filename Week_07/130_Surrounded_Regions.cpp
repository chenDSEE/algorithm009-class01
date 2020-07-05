// BFS version


// DFS version

// DSU version
class DSU {
private:
    int *parent;

public:
    DSU(const int n) {
        parent = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
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

        parent[root_two] = root_one;
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

        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                if (round_set.is_connected(x *col + y, virtual_node)) {
                    board[x][y] = 'O';
                } else {
                    board[x][y] = 'X';
                }
            }
        }

        return ;
    }
};