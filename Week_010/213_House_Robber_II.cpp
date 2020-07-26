/**
 * 这个题与上一个题的区别在于，房屋是环形的，这意味着，第一个房间和最后一个房间不能同时偷窃。
 * 这就意味着，将原来的问题转化为两个子问题：偷窃1 ~ n-1个房间的最大值以及偷窃 2~n 个房间的最大值。
 * 最终，取二者的最大值即为解因此可以对上一个问题进行两次dp即可。
 */
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        // max(不抢最后一家, 抢最后一家)
        return max(rob_range(nums, 0, nums.size() - 2), rob_range(nums, 1, nums.size() - 1));
    }

private:
    int rob_range(vector<int> &nums, int start, int end) {
        if (nums.size() == 0 || start < 0 || end > nums.size()) {
            return 0;
        }

        int first_dp = 0, second_dp = nums[start];
        for (int who = start + 1; who <= end; who++) {
            int curr_dp = max(nums[who] + first_dp, second_dp);
            first_dp = second_dp;
            second_dp = curr_dp;
        }

        return second_dp;
    }
};