class Solution {
public:
    string toLowerCase(string str) {
        for (char &c : str) {
            if (c >= 'A' && c <= 'Z') {
                c += 'a' - 'A';
            }
        }

        return str;
    }
};

// bit operation
/**
 * 大写变小写、小写变大写 : 字符 ^= 32;
 * 大写变小写、小写变小写 : 字符 |= 32;  
 * 小写变大写、大写变大写 : 字符 &= -33;
 */

class Solution {
public:
    string toLowerCase(string str) {
        for(auto &s : str) {
//            if (s >= 'A' && s <= 'Z')
                s |= 'a' - 'A';
        }

        return str;
    }
};

class Solution {
public:
    string toLowerCase(string str) {
        for (int index = 0; index < str.size(); index++) {
            if (str[index] >= 'A' && str[index] <= 'Z') {
                str[index] += 'a' - 'A';    // good point
            }
        }

        return str;
    }
};

