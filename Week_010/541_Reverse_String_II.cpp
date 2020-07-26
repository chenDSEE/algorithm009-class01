/* Example Version */
class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += 2*k) {
            reverse(s.begin() + i, min(s.begin() + i + k, s.end()));
        }

        return s;
    }
};



// better to understand
class Solution {
public:
    string reverseStr(string s, int k) {
        for (int offset = 0; offset < s.size(); offset += 2 * k) {
            int start = offset;

            // 末尾究竟是否比 k 多。末尾情况时，将会发生 start > mid, 动态收缩末尾
            int mid = min(start + k - 1, int(s.size() - 1);
            if (start < mid) {  // 本次还有多少的旋转的，末尾情况下，下一次将不可能进入这里
                reverse(s.begin() + start, s.begin() + mid + 1);
            }
        }

        return s;
    }
};
