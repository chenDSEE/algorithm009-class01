/**
 * 对齐，然后比较并输出结果
 *
 * flower
 * flow
 * flight
 *
 */

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0)
            return "";

        string answer;
        for (int col = 0; col < strs[0].size(); col++) {
            char target = strs[0][col];
            for (int row = 1; row < strs.size(); row++) {
                if (col >= strs[row].size() || strs[row][col] != target) { // 前面的是为了让最短的中间 row string 直接输出
                    return answer;
                }
            }
            answer += target;
        }

        return strs[0];
    }
};

/* Trie Version */
