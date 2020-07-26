class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> answer;
        if (p.size() > s.size()) {
            return answer;
        }

        unordered_map<char, int> target;
        unordered_map<char, int> window;    // 次数统计，更多的是通过双指针的方式模拟 window
        for (char c : p) {
            target[c]++;
        }

        int left = 0, right = 0;    // window pos，用来模拟 window
        int match_cnt = 0;          // 有几个字母的出现次数跟 target 一致的

        while (right < s.size()) {
            // update new char into window right side
            char input = s[right];
            right++;
            if (target.count(input) == 1) { // 当 当前字母 是存在于 p 的，我们才把他放进 window 里面
                window[input]++;
                if (window[input] == target[input]) {   // 说明有一个字母完全 match 上了 target
                    match_cnt++;
                }
            }

            // remove old char from window left side
#if 0
            while (right - left >= p.size()) {
#else
            if (right - left >= p.size()) {
#endif
                if (match_cnt == target.size()) {   // check match_cnt, and update answer
                    answer.emplace_back(left);
                }

                char remove = s[left];
                left++;
                if (target.count(remove) == 1) {
                    if (window[remove] == target[remove]) {
                        match_cnt--;
                    }

                    window[remove]--;
                }
            }
        }   // end of while

        return answer;
    }
};

// 简化版本
