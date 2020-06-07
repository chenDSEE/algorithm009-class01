class Solution {
private:
    unordered_set<int> column;
    unordered_set<int> left;
    unordered_set<int> right;
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> answer;
        vector<int> one;
        solveNQueens_split(answer, one, n);
        return answer;
    }

    void solveNQueens_split(vector<vector<string>> &answer, vector<int> &one, int n) {
        int row = one.size();
        // trem
        if (row == n) {
            draw_answer(answer, one);
            return ;
        }

        // drill
        for (int curr_col = 0; curr_col < n; curr_col++) {
            if (is_valid_queen(row, curr_col)) {

                one.push_back(curr_col);
                column.insert(curr_col);
                left.insert(row + curr_col);
                right.insert(row - curr_col);

                solveNQueens_split(answer, one, n);

                one.pop_back();
                column.erase(curr_col);
                left.erase(row + curr_col);
                right.erase(row - curr_col);
            }
        }

    }

    void draw_answer(vector<vector<string>> &answer, const vector<int> &one) {
        string s_tmp(one.size(), '.');
        vector<string> tmp;
        for (int row = 0; row < one.size(); row++) {
            s_tmp[one[row]] = 'Q';
            tmp.push_back(s_tmp);
            s_tmp[one[row]] = '.';
        }

        answer.push_back(tmp);
    }

    bool is_valid_queen(int row, int col) {
        return (column.count(col) == 0 && left.count(row + col) == 0 && right.count(row - col) == 0);
    }
};