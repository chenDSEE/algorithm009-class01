class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (target == nums[mid])
                return mid;

            if (nums[mid] >= nums[left]) {  // 先判断在那一截上面
                // 在根据对应截的单调性，看看 target 在不在这一截中，再决定左右边界的移动方案
                if (target >= nums[left] && target < nums[mid]) 
                    right = mid - 1;
                else
                    left = mid + 1;

            } else {
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;

            }

        }   // end of while

        return -1;
    }
};


#include <vector>
#include <iostream>

int
find_point(std::vector<int> &test_case)
{
    int left = 0, right = test_case.size() - 1;
    int target = 0;
    while (left < right) {
        int mid = (left + right) >> 1;
        if (test_case[mid] > test_case[mid + 1])
            return mid;

        if (test_case[mid] >= test_case[left])
            left = mid + 1;
        else
            right = mid - 1;

    } // end of while

    return left;
}

int main()
{
    std::vector<int> test_case;
//    test_case.emplace_back(4);
//    test_case.emplace_back(5);
//    test_case.emplace_back(6);
//    test_case.emplace_back(7);
//    test_case.emplace_back(0);
//    test_case.emplace_back(1);
//    test_case.emplace_back(2);

    test_case.emplace_back(3);
    test_case.emplace_back(1);

    std::cout << find_point(test_case) << std::endl;
    return 0;
}