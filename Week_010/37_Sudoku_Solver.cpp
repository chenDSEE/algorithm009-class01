class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        if (board.size() == 0)
            return ;

        DFS_solve(board);
    }

    bool DFS_solve(vector<vector<char>> &board) {
        for (int x = 0; x < board.size(); x++) {
            for (int y = 0; y < board[x].size(); y++) {
                if (board[x][y] == '.') {
                    for (char curr = '1'; curr <= '9'; curr++) {
                        if (is_vailed(board, x, y, curr)) {
                            board[x][y] = curr;
                            if (DFS_solve(board))
                                return true;

                            board[x][y] = '.';
                        }
                    }

                    return false;
                }
            }
        }

        return true;
    }

    bool is_vailed(vector<vector<char>> &board, int x, int y, char curr) {
        for (int cnt = 0; cnt < 9; cnt++) {
            if (board[x][cnt] != '.' && board[x][cnt] == curr) 
                return false;
            if (board[cnt][y] != '.' && board[cnt][y] == curr) 
                return false;
            if (board[(x / 3) * 3 + cnt / 3][(y / 3) * 3 + cnt % 3] != '.' 
                && board[(x / 3) * 3 + cnt / 3][(y / 3) * 3 + cnt % 3] == curr) 
                // [行数偏移 + block 内偏移（每三个加一次）][列数偏移 + block 内偏移（每一个加一次，012 循环）]
            {
                return false;
            }
        }

        return true;
    }

};


// smaller version but need to opt and speed up
class Solution {
private:
    unordered_set<char> row_record[9];
    unordered_set<char> col_record[9];
    unordered_set<char> block_record[9];
    vector<pair<int, int>> not_fill;    // row -> col   

public:
    void solveSudoku(vector<vector<char>>& board) {
        if (board.size() == 0)
            return ;

        for (char c = '1'; c <= '9'; c++) {
            for (int num = 0; num < 9; num++) {
                row_record[num].insert(c);
                col_record[num].insert(c);
                block_record[num].insert(c);
            }
        }
        

        for (int x = 0; x < board.size(); x++) {
            for (int y = 0; y < board.size(); y++) {
                if (board[x][y] != '.') {
                    row_record[x].erase(board[x][y]);
                    col_record[y].erase(board[x][y]);
                    block_record[(x / 3) * 3 + y / 3].erase(board[x][y]);

                } else {
                    not_fill.emplace_back(pair<int, int> {x, y});
                }
            }
        }

        DFS_solve(board, 0);
    }

    bool DFS_solve(vector<vector<char>> &board, int curr) {
        if (curr == not_fill.size())
            return true;

        int x = not_fill[curr].first, y = not_fill[curr].second;
        int block = (x / 3) * 3 + y / 3;
        for (char one = '1'; one <= '9'; one++) {
            if (row_record[x].count(one) == 1 
                && col_record[y].count(one) == 1
                && block_record[block].count(one) == 1)
            {
                board[x][y] = one;
                row_record[x].erase(one);
                col_record[y].erase(one);
                block_record[block].erase(one);

                if (DFS_solve(board, curr + 1))
                    return true;

                row_record[x].insert(one);
                col_record[y].insert(one);
                block_record[block].insert(one);
            }
        }

        return false;
    }
};