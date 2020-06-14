class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int g_cnt = 0, s_cnt = 0;
        while (g_cnt < g.size() && s_cnt < s.size()) {
            if (g[g_cnt] <= s[s_cnt]) 
                g_cnt++;

            s_cnt++;
            
        }   // end of while

        return g_cnt;
    }
};