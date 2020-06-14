class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> answer;
        vector<int> queen_pos;
        solve_n_queens_split(answer, queen_pos, n);        
        return answer;
    }

    void solve_n_queens_split(vector<vector<string>> &answer, vector<int> &queen_pos, int n) {
        if (queen_pos.size() >= n) {
            draw_queen(answer, queen_pos);
            return ;
        }

        int y = queen_pos.size() - 1;
        for (int x = 0; x < n; x++) {
            if (column.count(x) == 0 && left.count(x + y) == 0 && right.count(y - x) == 0) {
                queen_pos.emplace_back(x);
                column.insert(x);
                left.insert(x + y);
                right.insert(y - x);

                solve_n_queens_split(answer, queen_pos, n);

                queen_pos.pop_back();
                column.erase(x);
                left.erase(x + y);
                right.erase(y - x);
            }
        }

        return ;
    }

private:
    unordered_set<int> column;
    unordered_set<int> left;    // y + x
    unordered_set<int> right;   // y - x
    
    void draw_queen(vector<vector<string>> &answer, vector<int> &queen_pos) {
        answer.emplace_back(vector<string> {});
        string tmp(queen_pos.size(), '.');
        for (int pos : queen_pos) {
            tmp[pos] = 'Q';
            answer.back().emplace_back(tmp);
            tmp[pos] = '.';
        }

    }
};
