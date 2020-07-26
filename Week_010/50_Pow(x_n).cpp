class Solution {
public:
    double myPow(double x, int n) {
        // 很重要的转换判断，负数极限 的绝对值 是比 正数大一的，因为 -0 拿来标识最大负数了 ！
        // if(n<0) return 1/x * myPow(1/x, -(n+1));   这种方式也可以绕开这个问题
        long long N = n;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }

        return new_pow(x, N);
    }

    double new_pow(double x, long long n) {
        if (n == 0)
            return 1.0;
        
        double answer = new_pow(x, n / 2);

        return n % 2 ? answer * answer * x : answer * answer;
    }
};


/* 不扩大的方案 */
