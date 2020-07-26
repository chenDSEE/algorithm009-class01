/**
 * 排序算法的稳定性：
 * 稳定性排序保证了：
 * 两个相等的数之间的相对位置，在排序之后也不会发生改变。
 * a = 10, b = 10; 排序前 {a, b}, 排序后还是 {a, b}; 而不会出现 {b, a} 这样的情况
 */

/* Selection Sort - 选择排序 - O(n^2) */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        for (int cnt = 0; cnt < nums.size(); cnt++) {
            int min_index = cnt;
            for (int check = cnt + 1; check < nums.size(); check++) {
                if (nums[min_index] > nums[check]) {
                    min_index = check;
                }
            }

            int tmp = nums[cnt];
            nums[cnt] = nums[min_index];
            nums[min_index] = tmp;
        }

        return nums;
    }
};

/* Insertion Sort - 插入排序 - O(n^2) */
// 先暂存这个每一个 nums[check]，然后将之前的元素逐个后移，留出空位，插入到合理的顺序中
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        for (int unsort_index = 1; unsort_index < nums.size(); unsort_index++) {
            int tmp = nums[unsort_index];
            int move_index = unsort_index;
            while (move_index > 0 && tmp < nums[move_index - 1]) {
                nums[move_index] = nums[move_index - 1];
                move_index--;
            }

            nums[move_index] = tmp; // insert the num[unsort_index] into the right pos
        }

        return nums;
    }
};

/* Bubble Sort - 冒泡排序 - O(n^2) */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        for (int round = 0; round < nums.size(); round++) { // 每一将一个数字进行排序（每一轮把遇到的最大值扔到这一轮的末尾）
            for (int check = 1; check < nums.size() - round; check++) { // 把这一轮遇上的最大值放到这一轮的最末尾
                if (nums[check - 1] > nums[check]) {
                    int tmp = nums[check - 1];
                    nums[check - 1] = nums[check];
                    nums[check] = tmp;
                }
            }
        }

        return nums;
    }
};

/* Quick Sort - 快速排序 - O(n * log n) */
/**
 * 通过递归分治的方式实现排序
 * 1. 每一个分组中，随机选择一个标杆，然后将标杆大于标杆、小于标杆的数字分别无序的放在标杆两边
 * 2. 以此类推，对每一个分组都执行这样的操作，最后实现排序
 *
 * NOTE: 为何这个是不稳定的排序 ？
 * 因为发生 if 的判断，并发生位置移动操作的时候，并不是已经能够保证有序了，这个位置移动的操作，日后很有可能要再来一次（重复了）
 * 在移动别人的位置之前，并没有办法明确：我移动的各个数字都是有序的，所以也就没有办法很高效、精准的移动位置，
 * 要多重复几次，来提高精确度，确保放的位置时最终准确的
 */

/**
 * 6. Quick sort:
 *     Worstcase time: O(n^2), Bestcase Time: O(nlogn), Ave: O(nlogn), Space: O(1)-- not including recursive function stack space.
 *     Quicksort uses divide-and-conquer approach.
 *     1. Base operation: find pivot element
 *     2. Divide and concure art: divide the array into two halves and recursselvy quicksort the array
 *     3. Combine part do nothing
 *     best case and avg case when partition element is around middle and in that case
 *     T(n) = O(n) + 2T((n-1)/2) + Nothing -- best case 
 *     T(n) = O(n) + T(9n/10)+ T(n/10) -- > O(n logn) -- averge case
 *     Worstcase when partition element is around start and end every time -- revered sorted input list provided here:
 *     T(n) = O(n) + T(n-1) + Nothing -- > O(n + n-1 + n-2 + .. ) --> O(n^2)
 *     We can use randomized quicksort which gives worst case complexity as O(n logn) by picking pivot element randomly.  But it can not gurantee, complexity can go to O(n^2) here also.
 */

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size() - 1);
        return nums;
    }

private:
    void quick_sort(vector<int> &nums, int start, int end) {
        if (end <= start)   // 防止数组越界的情况进行计算
            return ;

        int pivot = partition(nums, start, end);

        quick_sort(nums, start, pivot - 1);
        quick_sort(nums, pivot + 1, end);
    }

    int partition(vector<int> &nums, int start, int end) {
        // pivot_pos -> 分界点位置，count_pos -> 小于 nums[pivot_pos] 的元素数量 的 位置
        int pivot_pos = end;    // 随意选择
        int count_pos = start;
        for (int index = start; index < end; index++) {    // 将每一个小于 nums[pivot_pos] 的元素放到最开始的地方
            if (nums[index] < nums[pivot_pos]) {
                int tmp = nums[count_pos];
                nums[count_pos] = nums[index];
                nums[index] = tmp;

                count_pos++; // 更新下一个可供刷写的位置
            }
        }

        int tmp = nums[count_pos];
        nums[count_pos] = nums[pivot_pos];
        nums[pivot_pos] = tmp;

        return count_pos;
    }
};

// not good enought version
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size() - 1);
        return nums;
    }

private:
    void quick_sort(vector<int> &nums, int start, int end) {
        if (end <= start)
            return ;

        int pivot = start;
        int left_pos = start;
        int right_pos = end;
        while (left_pos < right_pos) {
            while (left_pos < right_pos && nums[right_pos] > nums[pivot]) {
                right_pos -= 1;
            }
            while (left_pos < right_pos && nums[left_pos] <= nums[pivot]) {
                left_pos += 1;
            }

            swap(nums[left_pos], nums[right_pos]);
        }   // end of while

        swap(nums[pivot], nums[right_pos]);

        quick_sort(nums, start, right_pos - 1);
        quick_sort(nums, right_pos + 1, end);
    }
};

/* Merge sort - 归并排序 - O(n * log n) */
/**
 * 4. Merge sort: (divide and concur)
 *    Worstcase time: O(nlogn), Bestcase Time: O(nlogn), Space: O(n) (not considering recursion call stack space)
 *    It is a divide and concure technique which 
 *    Divide: Break the given problem into sub-problems of same type.
 *    Conquer: Recursively solve these sub-problems
 *    Combine: Appropriately combine the answers
 *    1. Base operation: find the mid elemet
 *    2. Divide and  concure part: divide the array into two halves and recursively solve these sub-problems
 *    3. Combine part: appropriately add sorted two halves arrays
 *    T(n) = 0(1)(Finding mid index -- preprocessing) + 2T(n/2) + O(N) (merging - postprocessing)
 *    T(n) = 2T(n/2) + O(n) --> O(nlong)
 *    T(N) = aT(n/b) + f(n) -- >  logn(baseb) is the height and max no of leafs is a^heigh and total number a^(height+1)-1 (Here n is the length of the array)
 *    According to master method:
 *    T(N) = aT(n/b) + f(n)
 *    T(n) = Θ(nloga(baseb)) when f(n) has slower growth that n^loga(baseb)
 *    T(n) = Θ(nloga(baseb) log n) when f(n) has equal growth that n^loga(baseb)
 *    T(n) = Θ(f(n)) when f(n) has faster growth that n^loga(baseb) 
 */

class Solution {
private:
    vector<int> temp;
public:
    vector<int> sortArray(vector<int>& nums) {
        temp.resize(nums.size(), 0);
        merge_sort(nums, 0, nums.size() - 1);
        return nums;
    }

private:
    void merge_sort(vector<int> &nums, int left, int right) {
        if (left >= right)
            return ;

        int mid_pos = (left + right) >> 1; // 可以随机选择，但通常情况下 二分 看起来时最高效的
        merge_sort(nums, left, mid_pos);
        merge_sort(nums, mid_pos + 1, right);

        merge_up(nums, left, mid_pos, right);   
    }

    void merge_up(vector<int> &nums, int left, int mid, int right) {
        int L = left, R = mid + 1, index = 0;

        while (L <= mid && R <= right) {    // untill one group is empty
            temp[index++] = nums[L] <= nums[R] ? nums[L++] : nums[R++];
        }

        // 清空剩余的数组
        while (L <= mid) {
            temp[index++] = nums[L++];
        }
        while (R <= right) {
            temp[index++] = nums[R++];
        }

        // 向 nums 合并两个数组
        for (int i = 0; i < right - left + 1; i++) {
            nums[left + i] = temp[i];
        }
    }
};


/* heap sort - 堆排序 - O(2 * n * logn) */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        heap_sort(nums);
        return nums;
    }

private:
    void heap_sort(vector<int> &nums) {
        if (nums.size() == 0)
            return ;

        int len = nums.size();
        // construct max-heap
        // 此时我们从最后一个非叶子结点开始，从左至右，从下至上进行调整。
        // 叶结点自然不用调整，因为我们在调整每一个叶子节点的父节点时，就会调整到它们
        for (int node_pos = len / 2 - 1; node_pos >= 0; node_pos--) {
            heapify(nums, len, node_pos);
        }

        // 1.将最大值排列到数组的最后面；
        // 2.整理 heap, 把新的堆顶下沉到合适的位置
        // 3.把新的最大值（第二大），拍到数组的倒数第二位置，以此类推；
        for (int last_pos = len - 1; last_pos >= 0; last_pos--) {
            int tmp = nums[0];
            nums[0] = nums[last_pos];
            nums[last_pos] = tmp;

            heapify(nums, last_pos, 0); // 切记，缩小数组的最末尾位置，同时把新的堆顶安定下来
        }
    }

    // 堆：父节点大于两个子节点，只能够找到最大值\最小值，其他的信息统统不记录
    void heapify(vector<int> &nums, int len, int root_pos) {
        int left_pos = 2 * root_pos + 1, right_pos = 2 * root_pos + 2;
        int max_pos = root_pos; // 假设父节点最大

        // 看看左节点跟父节点的大小情况
        if (left_pos < len && nums[left_pos] > nums[max_pos]) {
            max_pos = left_pos;
        }
        // 看看右节点跟父节点\左节点的大小情况
        if (right_pos < len && nums[right_pos] > nums[max_pos]) {
            max_pos = right_pos;
        }

        // 需要更新本层状况，并进一步下探
        if (max_pos != root_pos) {
            int tmp = nums[root_pos];
            nums[root_pos] = nums[max_pos];
            nums[max_pos] = tmp;

            // drill down
            heapify(nums, len, max_pos);
        }
    }
};

// STL version
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> heap;

        for (int i = 0; i < nums.size(); i++) {
            heap.push(nums[i]);
        }

        for (int i = 0; i < nums.size(); i++) {
            nums[i] = heap.top();
            heap.pop();
        }

        return nums;
    }
};