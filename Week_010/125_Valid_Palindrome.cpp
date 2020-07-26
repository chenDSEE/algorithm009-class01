
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        while (left < right) {
            if (!((s[left] >= '0' && s[left] <= '9') || (s[left] >= 'a' && s[left] <= 'z'))) {
                cout << s[left] << endl;
                left++;
                continue;
            }
            if (!((s[right] >= '0' && s[right] <= '9') || (s[right] >= 'a' && s[right] <= 'z'))) {
                cout << s[right] << endl;
                right--;
                continue;
            }

            if (s[left] != s[right])
                return false;

            left++;
            right--;
        }   // end of while

        return true;
    }
};


// better version

class Solution {
public:
    bool isPalindrome(string s) {
        string tmp;
        for (char one : s) {
            if (isalnum(one))
                tmp += tolower(one);
        }

        int left = 0, right = tmp.size() - 1;
        while (left < right) {
            if (tmp[left] != tmp[right])
                return false;

            left++;
            right--;
        }   // end of while

        return true;
    }
};



class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            while (left < right && !isalnum(s[right])) {
                right--;
            }

            if (tolower(s[left]) != tolower(s[right]))
                return false;

            left++, right--;
        }   // end of while

        return true;
    }
};
