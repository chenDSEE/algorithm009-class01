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
                    while (left < right && nums[left] == nums[++left]);     // search next right answer and make while-loop break
                    while (left < right && nums[right] == nums[--right]);
                }

            } // end of while (left < right)
        }

        return answer;
    }
};


/**
 * question point:
 * 1. 怎么找到可以作为结果的三元组组合？
 * 2. 怎么对三元组组合进行去重 ？
 * 
 * solution:
 * 1. 首先自然是最简单的暴力破解，i\j\k 三个起去进行遍历，然后去重。
 *    但是你会发现很麻烦的问题，三元组去重十分蛋疼。
 * 
 *    既然找到结果之后去重很蛋疼，那样还不如开始思考怎么在计算之前就进行去重，这样
 *    效率来得更高
 * 2. 排序、set 都可以进行去重，甚至你可以手动的一一循环去重！
 * 2.1 采用排序去重的话，你要思考的问题就是，怎么跳过相同的元素，target、left、right 都要跳过
 *     而且排序带来了另一个便利之处：sum 变得有规律了。target\left\right >\< 0 这样的组合是不可以的，提前跳过
 *     而且 target < left < right 恒成立。所以 target > 0 的时候就可以不用继续下去了
 * 
 * 2.2 剩下的就是 left、right 向中间靠拢，寻找 target 的事了。
*/