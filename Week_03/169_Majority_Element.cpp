class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> data_map;
        for (int check : nums) {
            data_map[check]++;
            if (data_map[check] > nums.size() / 2)
                return check;
        }

        // should not be here
        return -1;
    }
};

// 排序后去中间！因为众数的数量的 大于 n / 2 的，所以奇数偶数也没什么关系
// 也是因为大于一半，所以排序之后一定是有超过一半的数字相同，所以中间的一定是 众数
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};


/* divide-and-conquer */
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        return majorityElement_spilt(nums, 0, nums.size() - 1);
    }

    int majorityElement_spilt(const vector<int> &nums, int left_pos, int right_pos) {
        /* base case; the only element in an array of size 1 is the majority element. */
        // termi
        if (left_pos == right_pos)
            return nums[left_pos];

        /* recurse on left and right halves of this slice. */
        // process
        int mid_pos = (right_pos - left_pos) / 2 + left_pos;

        // drill
        int left_ME = majorityElement_spilt(nums, left_pos, mid_pos);
        int right_ME = majorityElement_spilt(nums, mid_pos + 1, right_pos);

        /* if the two halves agree on the majority element, return it. */
        // merge
        if (left_ME == right_ME)
            return left_ME;

        /* otherwise, count each element and return the "winner". */
        int left_cnt = get_count_range(nums, left_ME, left_pos, right_pos);
        int right_cnt = get_count_range(nums, right_ME, left_pos, right_pos);

        return left_cnt > right_cnt ? left_ME : right_ME;
    }

    /* count the numbers in range */
    int get_count_range(const vector<int> &nums, int target, int left_pos, int right_pos) {
        int cnt = 0;
        for (int i = left_pos; i <= right_pos; i++) {
            if (nums[i] == target)
                cnt++;
        }

        return cnt;
    }
};