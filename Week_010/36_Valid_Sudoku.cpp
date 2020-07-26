class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row = board.size(), col = board[0].size();
        unordered_set<int> col_record[9];
        unordered_set<int> row_record[9];
        unordered_set<int> block_record[9];

        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                if (board[x][y] != '.') {
                    int target = board[x][y] - '0';
                    int bolck_num = (x / 3) * 3 + y / 3;
                    if (col_record[y].count(target) == 1
                        || row_record[x].count(target) == 1
                        || block_record[bolck_num].count(target) == 1)
                    {
                        return false;
                    }

                    row_record[x].insert(target);
                    col_record[y].insert(target);
                    block_record[bolck_num].insert(target);
                }
            }
        }
        
        return true;
    }
};