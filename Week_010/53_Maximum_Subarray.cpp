/* 分治版本 */

/* DP Version */
/**
 * 重点三步走：
 * 1. 分治怎么分（子问题）：max_sum(i) = Max(max_sub(i - 1), 0) + a[i];
 *    怎么把一个大的问题切分，达到：能够有选择性的继承旧有的历史影响
 * 2. 状态数组怎么定义，怎么来记录旧的状态
 * 3. DP 方程：f[i] = Max(f[i - 1], 0) + a[i];
 *
 * 本题核心：
 * 当前最大子序列和 = 只选择当前元素自己，或包含之前的元素后会更大（比 0）
 * 毕竟，之前小于 0 的结果和完全没有包含起来的必要
 */

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp_status(nums.size(), 0);
        int max_result = INT_MIN;

        dp_status[0] = nums[0];
        max_result = max_result > dp_status[0] ? max_result : dp_status[0];
        for (int index = 1; index < nums.size(); index++) {
            dp_status[index] = nums[index] + std::max(dp_status[index - 1], 0);
            max_result = max_result > dp_status[index] ? max_result : dp_status[index];
        }

        return max_result;
    }
};

/* 状态压缩 DP */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        int prev_sum = nums[0];
        int max_sum = nums[0];
        for (int cnt = 1; cnt < nums.size(); cnt++) {
            prev_sum = max(nums[cnt], prev_sum + nums[cnt]);
            max_sum = max(max_sum, prev_sum);
        }

        return max_sum;
    }
};