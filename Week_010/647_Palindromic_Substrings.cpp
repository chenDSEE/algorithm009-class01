class Solution {
public:
    int countSubstrings(string s) {
        if (s.empty()) 
            return 0;

        int size = s.size(), answer = 0;
        vector<vector<bool>> dp(size, vector<bool>(size));

        for (int row = size - 1; row >= 0; --row) {
            for (int col = row; col < size; ++col) {
                dp[row][col] = (s[row] == s[col]) && (col - row <= 2 || dp[row + 1][col - 1]);
                if (dp[row][col]) ++answer;            
            }            
        }
        return answer;
    }
};
