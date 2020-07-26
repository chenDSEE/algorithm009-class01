class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.empty())
            return false;

        int prev_jump_pos = nums.size() - 1;
        for (int curr_pos = nums.size() - 1; curr_pos >= 0; curr_pos--) {
            if (nums[curr_pos] + curr_pos >= prev_jump_pos)
                prev_jump_pos = curr_pos;

        }

        return prev_jump_pos == 0 ? true : false;
    }
};