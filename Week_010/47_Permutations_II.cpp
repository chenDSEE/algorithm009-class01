/* DFS Version */
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> answer;
        vector<bool> used(nums.size(), false);  // 记录已经用了那个坑位的数字
        vector<int> one;

        helper(answer, nums, used, one);
        return answer; 
    }

    void helper(vector<vector<int>> &answer, const vector<int> &nums, 
                vector<bool> &used, vector<int> &one) 
    {
        if (one.size() >= nums.size()) {
            answer.push_back(one);
            return ;
        }

        unordered_set<int> level_used;  // 记录这一层已经用过的数字（去重）
        for (int index = 0; index < nums.size(); index++) {
            if (used[index] == false && level_used.count(nums[index]) == 0) {
                level_used.insert(nums[index]);
                used[index] = true;
                one.push_back(nums[index]);

                helper(answer, nums, used, one);

                used[index] = false;
                one.pop_back();
            }
        }
    }
};


// another version
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> answer;
        vector<bool> used(nums.size(), false);
        vector<int> one;
        sort(nums.begin(), nums.end());
        helper(answer, nums, used, one);
        return answer; 
    }

    void helper(vector<vector<int>> &answer, const vector<int> &nums, 
                vector<bool> &used, vector<int> &one) 
    {
        if (one.size() >= nums.size()) {
            answer.push_back(one);
            return ;
        }


        for (int index = 0; index < nums.size(); index++) {
            //当前值用过了 或 
            //当前值等于前一个值： 两种情况：（有多个重复数字，仅仅说明不能再用一层重复使用，不同层是可以重复使用的）
            // 理论上是，一个个，逐渐标记 使用过的，但是你突然前面是没有用过的，那就证明你再同一层遍历
            // 紧挨着的话，是被使用过的，那你肯定进入了下一层
            //  1 nums[index-1] 没用过 说明是这一层用掉的，
            //  2 nums[index-1] 用过了 说明是上一层用掉的
            if (used[index] == true 
                || (index > 0 && nums[index] == nums[index - 1] && !used[index - 1])) 
            {
                continue;
            }


            used[index] = true;
            one.push_back(nums[index]);

            helper(answer, nums, used, one);

            used[index] = false;
            one.pop_back();
            
        }
    }
};

// 等价版本
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> answer;
        vector<bool> used(nums.size(), false);
        vector<int> one;
        sort(nums.begin(), nums.end());
        helper(answer, nums, used, one);
        return answer; 
    }

    void helper(vector<vector<int>> &answer, const vector<int> &nums, 
                vector<bool> &used, vector<int> &one) 
    {
        if (one.size() >= nums.size()) {
            answer.push_back(one);
            return ;
        }


        for (int index = 0; index < nums.size(); index++) {
            if (used[index] == true)
//                || (index > 0 && nums[index] == nums[index - 1] && !used[index - 1])) 
            {
                continue;
            }
/**
 * 当发生 nums[index] == nums[index - 1] 的时候，我不知道该不该跳过，要是在同一层的情况是肯定是要跳过的；
 * 但是发生在不同层的时候肯定是不用跳过的
 *
 * used[index - 1] == true, 说明是在不同层，安心使用；
 *     当上一个刚好是用过的话，那就说明自己在上一个数字的下一层。
 *     当上一个没有被用过，则是跟上一个处在相同层。同时，上一个相同的数字都没有被使用（被要求跳过了，又可以被分为：
 *         1. 自己刚刚被用完，回来了，所以从他开始接下来的同层，相同数字都不能用了，
 *         2. 到自己的时候，自己就已经被要求直接跳过了，因为跟上一个数字相同），
 *     那你岂不是也应该被跳过，除非你是下一层，否则同一层所有的相同数字都因该被跳过
 *
 * used[index - 1] == false, 说明自己的上一层数字并不是 在 index - 1 位置上的数字，另有其人。
 * 这时候就说明了：当前尝试的数字，跟上一个相同的数字是在同一层。同一层的的相同数字都会被视为一个数字，接下来说有相同的数字都要跳过。核心目的：跳过同一层的相同数字
 */

            used[index] = true;
            one.push_back(nums[index]);

            helper(answer, nums, used, one);

            used[index] = false;
            one.pop_back();
            
            int check;
            for (check = index; check < nums.size(); check++) {
                if (nums[check] != nums[index]) {
                    break;
                }
            }
            index = check - 1;
        }
    }
};

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> answer;
        vector<int> one;
        vector<bool> level_mark(nums.size(), false);
        std::sort(nums.begin(), nums.end());

        generate_permute_unique(answer, level_mark, one, 0, nums);

        return answer;
    }

    void generate_permute_unique(vector<vector<int>> &answer, vector<bool> &level_mark,
        vector<int> &one, int start, const vector<int> &nums)
    {
        if (one.size() >= nums.size()) {
            answer.emplace_back(one);
            return ;
        }

        for (int index = 0; index < nums.size(); index++) {
            if (level_mark[index] == true
                || (index > 0 && nums[index] == nums[index - 1] && level_mark[index - 1] == false))
            {
                continue;
            }

            one.emplace_back(nums[index]);
            // 相同数字之间的 true 是用来标记层次的；
            // 整个 level_mark 中的则是针对所有数字，标记谁被用过了
            level_mark[index] = true;

            generate_permute_unique(answer, level_mark, one, start + 1, nums);

            level_mark[index] = false;
            one.pop_back();
        }

        return ;
    }
};
