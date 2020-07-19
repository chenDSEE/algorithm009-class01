// 进行 k 次数组右移一位(超时，O(n ^ 2))
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int tmp = 0;
        for (int i = 0; i < k; i++) {
            tmp = nums[nums.size() - 1];
            for (int j = nums.size() - 2; j >= 0; j--) {
                nums[j + 1] = nums[j];
            }
            nums[0] = tmp;
        }              
    }
};

// 直接算出每一个元素的新坐标，然后交换临时数组
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        vector<int> tmp(nums.size());

        for (int cnt = 0; cnt < nums.size(); cnt++) {
            tmp[(cnt + k) % nums.size()] = nums[cnt];
        }

        swap(tmp, nums);
    }
};

// 逐个顶替掉
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        
        if (k < 0)
            k += nums.size();

        int next_pos = 0;

        for (int start = 0, cnt = 0; cnt < nums.size(); start++) {
            int curr_pos = start;
            int prev_val = nums[start];
            do {
                // find next index position
                // one replacement, you take prev to replace nums[next],
                // therefore you have to record prev and nums[next] !
                next_pos = (curr_pos + k) % nums.size();

                // insert prev_val and update prev_val
                int tmp = nums[next_pos];
                nums[next_pos] = prev_val;
                prev_val = tmp;

                // update for next round
                curr_pos = next_pos;

                // record for the end of for-loop
                cnt++;

            } while (next_pos != start); // comes across with begin
        }
    }
};


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        array_swap(nums, 0, nums.size() - 1);
        array_swap(nums, 0, k - 1);
        array_swap(nums, k, nums.size() - 1);
    }

    void array_swap(vector<int>& nums, int begin, int end) {
        if (nums.empty() || nums.size() < end) {
            return ;
        }

        while (begin < end) {
            int tmp = nums[end];
            nums[end] = nums[begin];
            nums[begin] = tmp;
            begin++;
            end--;
        }
    }
};


/* ================================================= */
// unknow ???  递归分治，日后再看
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size(), start = 0;
        for (; k %= n; n -= k, start += k) {
            for (int i = 0; i < k; i++) {
                swap(nums[start + i], nums[start + n - k + i]);
            }
        }
    }
};


public void rotate(int[] nums, int k) {
    recursiveSwap(nums, k, 0, nums.length);
}
private void recursiveSwap(int[] nums, int k, int start, int length) {
    k %= length;
    if (k != 0) {
        for (int i = 0; i < k; i++) {
            swap(nums, start + i, nums.length - k + i);
        }
        recursiveSwap(nums, k, start + k, length - k);
    }
}
private void swap(int[] nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

/* ================================================= */