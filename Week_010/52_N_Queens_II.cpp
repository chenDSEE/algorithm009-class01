// bit mask version
class Solution {
    int size;           // the size of board, size = n;
    int answer;

public:
    int totalNQueens(int n) {
        /**
         * influence: 1 -> is_used and will be influence by upper level;
         *            0 -> not-used and you can use in this level;
         *
         * the influence in this level:
         *                    board view
         * last_queen_pos: 0x 0000 0100;
         * this_left_inf : 0x 0000 1000;
         * next_left_inf : 0x 0001 0000;
         *                    ^       ^
         *      board[3][0] --+       +--- board[3][col - 1]
         */
        int      level_cnt = 0;  // count how many level of board had been filled
        uint32_t col_inf = 0;    // this col influence by upper level
        uint32_t left_inf = 0;   // this left line influence by upper level
        uint32_t right_inf = 0;  // this right line influence by upper level

        size = n;
        DFS_marking(0, 0, 0, 0);
        return answer;
    }

    void DFS_marking(int level_cnt, uint32_t col_inf, uint32_t left_inf, uint32_t right_inf) {
        if (level_cnt >= size) {
            answer++;
            return ;
        }

        /* get the position can place Queen and mark them by 1 */
        // 
        //   this_level_pos_can_be_used(mark by 1) 
        // = (~this_level_pos_can_not_be_used) & (0x0000 1111, n bit of 1);
        // 
        // this_level_pos_can_be_used is influence by upper Queen's column, left and right
        //
        // this_level_pos_can_be_used only used in this level of DFS !!!
        //     to know: in this level, how much and which pos still can be DFS tried
        uint32_t not_used_pos = (~(col_inf | left_inf | right_inf)) & ((1 << size) - 1);

        // if not_used_pos == 0, this meaning all the position can be placed Queen had been DFS search
        while (not_used_pos != 0) {
            uint32_t curr_queen_pos = not_used_pos & (-not_used_pos);
            not_used_pos = not_used_pos & (not_used_pos - 1);   // remove last 1, as mark this pos had been tried

            DFS_marking(level_cnt + 1, col_inf | curr_queen_pos, (left_inf | curr_queen_pos) << 1, (right_inf | curr_queen_pos) >> 1);

        }   // end of while

        return ;
    }
};

// set version
class Solution {
public:
    int totalNQueens(int n) {
        size = n;
        DFS_search(0);
        return answer;    
    }

private:
    unordered_set<int> col;
    unordered_set<int> left;
    unordered_set<int> right;
    int answer;
    int size;
    
    void DFS_search(int level) {
        if (level >= size) {
            answer++;
            return ;
        }

        for (int cnt = 0; cnt < size; cnt++) {
            if (col.count(cnt) == 0 && left.count(cnt + level) == 0 && right.count(level - cnt) == 0) {
                col.insert(cnt);
                left.insert(cnt + level);
                right.insert(level - cnt);

                DFS_search(level + 1);

                col.erase(cnt);
                left.erase(cnt + level);
                right.erase(level - cnt);
            }
        }

    }
};
