#define ONE_BIT 0x1

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t answer = 0;
        for (int cnt = 0; cnt < 32; cnt++) {
            uint32_t tmp = (n & 1) << (31 - cnt);
            answer += tmp;
            n >>= 1;
        }

        return answer;
    }
};

// 剪枝
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t answer = 0;
        int cnt = 0;
        while (n) {
            uint32_t curr = (n & 1) << (31 - (cnt++));
            answer += curr;
            n >>= 1;
        }

        return answer;
    }
};