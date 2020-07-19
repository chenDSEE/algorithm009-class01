class Solution {
public:
    int countSegments(string s) {
        int word_cnt = 0;
        for (int check = 0; check < s.size(); check++) {
            if (s[check] != ' ') {
                word_cnt++;
                while (check < s.size() && s[++check] != ' ');
            }
        }

        return word_cnt;
    }
};


// Straight Forward
class Solution {
public:
    int countSegments(string s) {
        int cnt = 0;
        int index = 0;
        while (index < s.size()) {
            while (index < s.size() && s[index] == ' ') {
                index++;
            }

            if (index == s.size()) {
                return cnt;
            }

            cnt++;
            while (index < s.size() && s[index] != ' ') {
                index++;
            }

            index++;
        }

        return cnt;
    }
};