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




class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> tmp(nums.size());
        int i = 0;
        for (i = 0; i < (k % nums.size()); i++) {
            tmp[i] = nums[nums.size() - (k % nums.size()) + i];
        }

        for (int j = 0; i < nums.size(); j++, i++) {
            tmp[i] = nums[j];
        }

        swap(tmp, nums);
    }
};


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        int cur = 0;
        int next = 0;
        int tmp = 0;
        int prev = 0;
        for (int start = 0, cnt = 0; cnt < nums.size(); start++) {
            cur = start;         
            prev = nums[start];
            do {          
                // one replacement, you take prev to replace nums[next],
                // therefore you have to record prev and nums[next] !
                next = (cur + k) % nums.size();
                tmp = nums[next];
                nums[next] = prev;

                // for next round
                cur = next;
                prev = tmp;

                // record for the end of for-loop
                cnt++;

            } while(cur != start);
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