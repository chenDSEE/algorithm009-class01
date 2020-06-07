class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> answer;
        vector<int> one;
        helper(answer, one, 0, n, k);
        return answer;
    }

    void helper(vector<vector<int>> &answer, vector<int> &one, int last, int n, int k) {
        if (k == 0) {
            answer.push_back(one);
            return ;
        }

        // i 的极限值满足： n - next + 1 = (k - pre.size())  当前还 能 找到几个数字 >= 当前还 要 找多少个数字
        // for (int next = last + 1; next <= n - (k - one.size()) + 1; next++)
        for (int next = last + 1; next <= n; next++) {
                one.push_back(next);
                helper(answer, one, next, n, k - 1);
                one.pop_back();
        }

        return ;
    }
};