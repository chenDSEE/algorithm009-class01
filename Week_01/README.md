# Week 01 作业总结

## 核心算法思想

- 空间换时间
- 思想的升维
  - 通过增加辅助信息、重新整理信息\数据 的方式，加速处理、遍历的过程
- 难度上的降维
  - 通过题目中的隐含信息（如：装最多水 中的宽度只能是单调递减），将本来高度、宽度两个不确定的增长方向减少至只剩下==高度==这一个既可以向上增长，又可以向下增长的不确定因素。由于宽度已经确定只会是==单调递减==的了，所以减少了一层对于宽度的循环
  - 这样就可以引入一种两边向中间夹逼的方案
- 先对数据进行调整、预处理，然后在解决问题
  - 将数组的==无序===>==有序==进行转换
  - 在 stack 的最底部填充 -1 作为判断基准
- 优化的方向：
  1. 首先的暴力求解
  2. 然后通过暴力求解，开始理解整个操作过程，并进一步汲取题目中提供的隐含信息
  3. 开始挖掘暴力求解方案中的重复部分，想办法跳过重复的部分（这个有可能要跟步骤二中的信息进一步结合）
  4. 思考是由否更适合的数据结构
  5. 思考是否需要引入辅助数据结构、预先梳理数据、预先设置 flag 标志数值，简化操作难度



## 来自题目中的思考

### 判重操作(3sum 与 Remove_Duplicates_from_Sorted_Array 的对比)

```c++
/* 26_Remove_Duplicates_from_Sorted_Array */

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i = 0, cnt = 0;
        nums.push_back(INT_MAX);
        while (i < nums.size() - 1) {
            nums[cnt++] = nums[i];
            while (nums[i] == nums[++i]);
        } // end of while (i < nums.size() - 1)

        nums.pop_back();
        return cnt;
    }
};

/**
 * if you want to use this 'while (nums[i] == nums[++i]);', you have to code 'nums.push_back(INT_MAX);' !
 * This is diff with 3sum !
 * In 3sum, 'while (left < right)' , what more the 'nums[++left]' will not overflow, beause right start at the position nums[num.size() - 1]
 * therefore 'left < right' make sure 'nums[++left]' will not overflow!
 * 
 * BUT In this, you can not use 'i < nums.size() - 1' to make sure 'nums[++i]' will not overflow !
 * If you do so, there will be an endless-loop ! For i have no way to self-add to over 'i < nums.size()' !
 * 
 * If you want to make use of the last one element in vector:
 * 1. make sure '++i' will not overflow;
 * 2. make sure you can self-add to jump out of the loop;
 * 
 * EXAMPLE:
 * 1. while (nums[i] == nums[++i]); you will overflow;
 * 2. while (i < nums.size() && nums[i] == nums[++i]); you can not make i self-add to 'i >= nums.size()';
 * 
 * all in all:
 * In 3sum:
 * while (left < right && nums[left] == nums[++left]);
 * > 1. break inner-while=loop, for 'nums[left] != nums[++left]', this is the next 'left' we need to compare
 * > 2. break inner-while=loop, for 'left < right', this will end both inner-while-loop and outer-while-loop !
 *      This is triggered by last '++left'.
 * 
 * In this:
 * while (i < nums.size() && nums[i] == nums[++i]);
 * 1. Last '++i' have no idea to trigger 'i < nums.size()' to break outer-while-loop !
 * 
 * Summary:
 * 1. '++i' must be trigger in all the round of loop, and last '++i' must trigger 
 *    the end of inner-loop(the first condition not satisfied)  and the outer-loop(also, the first condition not satisfied) !
 * 2. what's more, 'nums[++i]' can not be overflow !
*/




class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int cnt = 0;
        for (int i : nums) {
            if (cnt == 0 || i > nums[cnt - 1])  // you can make use of '||' to skip the first situation
                nums[cnt++] = i;
        }

        return cnt;
    }
};


/* 15_3Sum */

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> answer;
        if (nums.size() < 3)
            return answer;
        
        std::sort(nums.begin(), nums.end());
        for (int target = 0; target < nums.size() - 2; target++) {
            if (nums[target] > 0)
                break;
            if (target > 0 && nums[target] == nums[target - 1])
                continue;
            
            int left = target + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[target] + nums[left] + nums[right];
                if (sum < 0)
                    while (left < right && nums[left] == nums[++left]);     // 'left' can not self-add in for-loop !
                else if (sum > 0)
                    while (left < right && nums[right] == nums[--right]);   // 'right' can not self-add in for-loop !
                else {
                    answer.push_back(vector<int> {nums[target], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[++left]);
                    while (left < right && nums[right] == nums[--right]);
                }

            } // end of while (left < right)
        }

        return answer;
    }
};

```

