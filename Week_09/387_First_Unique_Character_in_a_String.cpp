/* 两端出发寻找 */
class Solution {
public:
    int firstUniqChar(string s) {
        for (int index = 0; index < s.size(); index++) {
            if (s.find(s[index]) == s.rfind(s[index])) {
                return index;
            }
        }

        return -1;
    }
};

/* 哈希数组 */
class Solution {
public:
    int firstUniqChar(string s) {
        int record[26] = {0};

        for (int index = 0; index < s.size(); index++) {
            record[s[index] - 'a']++;
        }

        for (int index = 0; index < s.size(); index++) {
            if (record[s[index] - 'a'] == 1) {
                return index;
            }
        }

        return -1;
    }
};

