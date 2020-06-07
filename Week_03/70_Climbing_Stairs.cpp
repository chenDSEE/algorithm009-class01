class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }

        int f1 = 1, f2 = 2, f3 = 0;
        // cnt < (n - 2) !
        for (int cnt = 0; cnt < (n - 2); cnt++) {
            f3 = f1 + f2;
            f1 = f2;
            f2 = f3;
        }

        return f3;
    }
};


/* recursion */
class Solution {
public:
    int climbStairs(int n) {
        // terim
        if (n <= 2) {
            return n;
        }

        return climbStairs(n - 1) + climbStairs(n - 2);
    }
};