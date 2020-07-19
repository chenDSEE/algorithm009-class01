class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                return sub_check(s, left + 1, right) || sub_check(s, left, right - 1);
            }
            left++;
            right--;
        }

        return true;
    }

private:
    bool sub_check(string &s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }

        return true;
    }
};