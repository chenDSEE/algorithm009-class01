class Solution {
public:
    int mySqrt(int x) {
        if (x <= 0)
            return 0;

        long left = 1, right = x;
        while (left <= right) {
            long mid = (left + right) >> 1; // speed up
            if (x < mid * mid) {    // 乘法比除法 快
                right = mid - 1;

            } else if (x > mid * mid) {
                left = mid + 1;

            } else {
                return mid;
            }

        }   // end of while

        return right;   // 因为输出结果使向下取整的，自然不能用最后还执行了 left -= 1; 的 left 啦
    }
};

class Solution {
public:
    int mySqrt(int x) {
        long new_x = x;
        while (new_x * new_x > x) {
            new_x = (new_x + x / new_x) >> 1;
        }

        return new_x;
    }
};