class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> max;
        vector<int> answer;

        if (k < 0 || nums.empty())
            return answer;

        for (int i = 0; i < nums.size(); i++) {
            // 去掉没有用的小数字
            while (!max.empty() && nums[i] > nums[max.back()]) {  // 只要没挖空，我就继续挖; 当相同的时候，两个都要保留
                max.pop_back();
            }

            max.push_back(i);

            // window.size() 不可能大于 k !
            if (i - max.front() >= k)
                max.pop_front();

            if (i + 1 >= k)
                answer.push_back(nums[max.front()]);
        }

        return answer;
    }
};

/**
 * you have to record index in window !
 * Or you have no idea to know the distance between head of window and the element you are checking !
 * When you pop_back element in window, you will loss the information about distance !
 * 
 * */

/* better version for variable name */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> answer;
        deque<int> window;

        if (k < 0 || nums.size() < k)
            return answer;

        for (int index = 0; index < nums.size(); index++) {
            while (!window.empty() && nums[window.back()] < nums[index]) {
                window.pop_back();
            }   // end of while

            window.push_back(index);

            if (index - window.front() >= k)
                window.pop_front();
            if (index + 1 >= k)
                answer.push_back(nums[window.front()]);
        }

        return answer;
    }
};