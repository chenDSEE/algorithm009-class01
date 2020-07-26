// skip k
class Solution {
public:
    bool validPalindrome(string s) {
        return sub_analy(s, 0, s.size() - 1, 2);
    }

private:
    bool sub_analy(string &s, int left, int right, int skip) {
        if (skip-- == -1) {
            return false;
        }

        while (left < right) {
            if (s[left] != s[right]) {
                return sub_analy(s, left + 1, right, skip) || sub_analy(s, left, right - 1, skip);
            }
            left++;
            right--;
        }

        return true;
    }
};


// skip 1
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