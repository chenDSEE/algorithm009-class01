/*
 *Given an array nums, write a function to move all 0's to the end of it while maintaining 
 *the relative order of the non-zero elements.
 *
 *Example:
 *Input: [0,1,0,3,12]
 *Output: [1,3,12,0,0]
 *
 *Note:
 * 1.You must do this in-place without making a copy of the array.
 * 2.Minimize the total number of operations.
 */

/**
 * 1. first_zero_position is the position for next Non-Zero number;
 * 2. You should take Non-Zero number rewrite the FIRST_zero_pos, BUT not LAST_zero_posision;
 * 3. The data in the left of first_zero_position are OK, you have no need to worry about them. 
 *    The continus data you should worry about is "cur" and the right of "cur";
 * 3.1 The data between (first_zero_position, cur) are 0, this small piece of data is OK too.
 *     They are all 0, no need to ordered again;
 * 
 * 
 * ELSE:
 * 1. https://leetcode.com/problems/move-zeroes/discuss/172432/THE-EASIEST-but-UNUSUAL-snowball-JAVA-solution-BEATS-100-(O(n))-%2B-clear-explanation
 * 2. https://leetcode.com/problems/move-zeroes/discuss/72132/One-line-c%2B%2B-code-20ms
 */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int cur = 0, first_zero_position = 0; cur < nums.size(); cur++) {
            if (0 != nums[cur]) {
                swap(nums[first_zero_position], nums[cur]);
                first_zero_position++;
            }
        }
    }
};

// 既然你从原理上发现，交换，那你就想清楚什么时候才交换
    // 要交换也就意味着，序列不对了，要发生改变
    // 不交换，也就意味着啥事都没有，可以不用别的操作了