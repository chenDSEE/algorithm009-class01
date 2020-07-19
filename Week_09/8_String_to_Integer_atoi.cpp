class Solution {
public:
    int myAtoi(string str) {
        if (str.size() == 0)
            return 0;

        int sign = 1;
        int index = 0;

        // remove space ' ';
        while (index < str.size() && str[index] == ' ') {
            index++;
        }

        // handle signs
        if (str[index] == '-' || str[index] == '+') {
            sign = str[index] == '-' ? -1 : 1;
            index++;
        }

        // hangle num
        int total = 0;
        while (index < str.size()) {
            int curr = str[index] - '0';
            if (curr < 0 || curr > 9)
                break;

            // check for overflow or underflow
            // total * 10 + curr > INT_MAX ==> 减法可以有效的避免溢出问题
            if (total > (INT_MAX - curr) / 10)
            {
                return sign == 1 ? INT_MAX : INT_MIN;
            }

            total = 10 * total + curr;
            index++;
        }

        return total * sign;
    }
};