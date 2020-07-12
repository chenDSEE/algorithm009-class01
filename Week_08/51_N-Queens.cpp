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


// better version
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<int> queen_pos;
        DFS_solve_queen(queen_pos, n);

        return answer;
    }

private:
    unordered_set<int> column;
    unordered_set<int> left;
    unordered_set<int> right;
    vector<vector<string>> answer; 

    void DFS_solve_queen(vector<int> &queen_pos, const int n) {
        if (queen_pos.size() == n) {
            answer.emplace_back(draw_board(queen_pos));
            return ;
        }

        int level = queen_pos.size();
        for (int pos = 0; pos < n; pos++) {
            if (column.count(pos) == 0 && left.count(pos + level) == 0 && right.count(level - pos) == 0) {
                queen_pos.emplace_back(pos);
                column.insert(pos);
                left.insert(pos + level);
                right.insert(level - pos);

                DFS_solve_queen(queen_pos, n);

                // revert
                queen_pos.pop_back();
                column.erase(pos);
                left.erase(pos + level);
                right.erase(level - pos);
            }
        }

        return ;
    }

    vector<string> draw_board(vector<int> &queen_pos) {
        vector<string> buf;
        string one(queen_pos.size(), '.');
        for (int cnt = 0; cnt < queen_pos.size(); cnt++) {
            one[queen_pos[cnt]] = 'Q';
            buf.emplace_back(one);
            one[queen_pos[cnt]] = '.';
        }

        return buf;
    }
};

// bit mask version(not my version !!!)
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        if (n < 1) return {};
        size = n;
        mask = (1 << n) - 1;

        vector<int> firstSol(n, 0);
        BackTrack(0, 0, 0, 0, firstSol);

        return GenRes();
    }

private:
    void BackTrack(int row, int left, int down, int right, vector<int> &curSol) {
        if (row == size) {
            binRes.push_back(curSol);
        } else {
            int bitmap = mask & ~(left | down | right);
            while (bitmap) {
                int pick = -bitmap & bitmap;
                curSol[row] = pick;
                BackTrack(row + 1, (pick | left) << 1, pick | down, (pick | right) >> 1, curSol);
                bitmap ^= pick;
            }
        }
    }

    vector<vector<string>> GenRes() {
        vector<vector<string>> res(binRes.size(), vector<string>(size, string(size, '.')));
        for (int i = 0; i < binRes.size(); ++i) {
            for (int j = 0; j < size; ++j) {
                int binIdx = binRes[i][j];
                int count = 0;
                while (binIdx) {
                    binIdx >>= 1;
                    ++count;
                }
                res[i][j][size - count] = 'Q';
            }
        }
        return res;
    }

    int size, mask;
    vector<vector<int>> binRes;
};


class Solution {
public:
    //根据qPos(皇后的位置)的值，构造输出的字符串
    void make_ret(int n,const vector<int>& qPos,vector<vector<string>>& answer) {
        vector<string> temp(n, string(n, '.'));
        for (int cnt = 0; cnt < n; cnt++) {
            temp[qPos[cnt]][cnt] = 'Q';
        }

        answer.push_back(temp);
    }

    void backtrack(int level,int n,int col,int hill,int dale,vector<int> &qPos,vector<vector<string>> &answer) {
        if (level >= n) {
            make_ret(n, qPos, answer);
            return ;
        }

        for (int cnt = 0; cnt < n; cnt++) {
            //检查col,hill,dale特定位上的值
            //如(1&col>>cnt)==0，就是检查col第c个比特位是否==0
            //level 表示行下标，cnt 表示当前的列下标，r+c与r-c值均为常数，注意：r-c有可能小于0，所以要+n
            if ((1 & (col >> cnt)) == 0 
                && (1 & hill >> (level + cnt)) == 0 
                && (1 & dale >> (level - cnt + n)) == 0) 
            {
                qPos[cnt] = level;
                //将col,hill,dale特定位的0置为1
                //如col|1<<c，就是将col第c个比特位的0变为1
                backtrack(level + 1, n, col | (1 << cnt), hill | (1 << level + cnt), dale | (1 << level - cnt + n), qPos, answer);
                qPos[cnt]=0;
            }

        }
    }
    
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string >>answer;
        vector<int> qPos(n);
        backtrack(0, n, 0, 0, 0, qPos, answer);
        return answer;
    }
};


class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        // 初始化一个棋盘，将棋盘中的点初始化为'.'
        vector<string> board(n, string(n, '.'));
        queen(0,0,0,0,n,board);
        return ans;
    }
    void queen(int l, int r, int m, int k, int n, vector<string> board){
        if(k == n){
            ans.push_back(board);
            return;
        }
        for(int i = ~(l|r|m)&((1<<n)-1); i;){
            int p = i&-i;
            board[k][log2(p)] = 'Q';
            queen((l|(i&-i))<<1,(r|(i&-i))>>1,m|(i&-i),k+1,n, board);
            board[k][log2(p)] = '.';
            i-=p;
        }
    }
private:
    vector<vector<string>> ans;
};
