// loop-n version
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;;
        while (n) {
            if (n & 0x1) {
                cnt++;
            }

            n >>= 1;
        }

        return cnt;
    }
};

// get last 1 bit
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int answer = 0;
        while (n) {
            n = n & (n - 1);
            answer++;
        }

        return answer;
    }
};
