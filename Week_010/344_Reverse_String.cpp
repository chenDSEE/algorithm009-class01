/* single pointer */
class Solution {
public:
    void reverseString(vector<char>& s) {
        int swap_len = s.size() >> 1;
        for (int index = 0; index < swap_len; index++) {
            swap(s[index], s[s.size() - 1 - index]);
        }
    }
};

/* two pointer version */
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            char tmp = s[left];
            s[left] = s[right];
            s[right] = tmp;

            left++;
            right--;
        }
    }
};