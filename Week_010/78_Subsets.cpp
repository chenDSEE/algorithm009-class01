class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> answer;
        vector<int> one;
        search_all(answer, one, nums, 0);
        return answer;
    }

    void search_all(vector<vector<int>> &answer, vector<int> &one, vector<int> &nums, int level) {
        if (level == nums.size()) {
            answer.push_back(one);
            return ;
        }

        search_all(answer, one, nums, level + 1);
        one.push_back(nums[level]);
        search_all(answer, one, nums, level + 1);

        one.pop_back();
    }
};

