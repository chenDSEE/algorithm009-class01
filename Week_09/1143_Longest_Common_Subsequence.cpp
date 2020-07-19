class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp_status(text1.size() + 1, vector<int>(text2.size() + 1, 0));

        for (int cnt_1 = 1; cnt_1 < text1.size() + 1; cnt_1++) {
            for (int cnt_2 = 1; cnt_2 < text2.size() + 1; cnt_2++) {
                // dp function
                if (text1[cnt_1 - 1] != text2[cnt_2 - 1]) {
                    dp_status[cnt_1][cnt_2] = max(dp_status[cnt_1][cnt_2 - 1], dp_status[cnt_1 - 1][cnt_2]);

                } else {
                    dp_status[cnt_1][cnt_2] = dp_status[cnt_1 - 1][cnt_2 - 1] + 1;
                }
            }
        }

        return dp_status[text1.size()][text2.size()];
    }
};