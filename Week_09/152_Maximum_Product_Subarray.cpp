// DP version
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max_val = nums[0], min_val = nums[0], answer = nums[0];
        for (int index = 1; index < nums.size(); index++) {
            if (nums[index] < 0) {
                std::swap(max_val, min_val);
            }

            // 计算出当前层的 max_val, 并保留历史上可能造成的 min_val，以备日后遇上一个负数的时候使用
            max_val = std::max(max_val * nums[index], nums[index]);
            min_val = std::min(min_val * nums[index], nums[index]);

            answer = max(answer, max_val);
        }

        return answer;
    }
};