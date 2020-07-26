class Solution {
public:
    bool isPerfectSquare(int num) {
        long left = 1;
        long right = num;
        while (left <= right) {
            long mid = left + ((right - left) >> 1);    // mid = left/2 + right/2
            long tmp = mid * mid;
            if (tmp == num)
                return true;

            if (tmp > num)
                right = mid - 1;
            else
                left = mid + 1;
        }

        return false;
    }
};


class Solution {
public:
    bool isPerfectSquare(int num) {
        long curr = num;
        while (curr * curr > num) {
            curr = (curr + num / curr) >> 1;
        }

        return curr * curr == num;
    }
};