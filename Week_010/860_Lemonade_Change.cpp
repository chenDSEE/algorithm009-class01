class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        vector<int> men_num(2, 0);    // 0 -> $5 numbers; 1 -> $10 number; 2 -> $20 number

        for (int one : bills) {
            if (one == 5) {
                men_num[0]++;

            } else if (one == 10) {
                if (men_num[0] <= 0)
                    return false;
                men_num[0]--;
                men_num[1]++;

            } else {
                if ((men_num[0] >= 1 && men_num[1] >= 1) 
                    || (men_num[0] >= 3))
                {
                    if (men_num[1] >= 1) {
                        men_num[1]--;
                        men_num[0]--;
                    } else {
                        men_num[0] = men_num[0] - 3;
                    }

                } else {
                    return false;
                }
            }
        }
        
        return true;
    }
};