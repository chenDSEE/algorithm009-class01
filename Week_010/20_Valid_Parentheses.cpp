class Solution {
public:
    bool isValid(string s) {
//        if (s.size() % 2 == 1)
//            return false;
// work by "return tmp_stack.empty()"

        stack<char> tmp;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(')
                tmp.push(')');
            else if (s[i] == '[')
                tmp.push(']');
            else if (s[i] == '{')
                tmp.push('}');
            else {
                if (tmp.empty() && s[i] != tmp.top())
                    return false;
                else
                    tmp.pop();
            }
        }

        return tmp.empty();
    }
};

// 剪枝
class Solution {
public:
    bool isValid(string s) {
        if (s.size() & 1)
            return false;

        stack<char> record;
        for (int index = 0; index < s.size(); index++) {
            if (s[index] == '(')
                record.push(')');
            else if (s[index] == '[')
                record.push(']');
            else if (s[index] == '{')
                record.push('}');
            else {
                if (record.empty() || record.top() != s[index])
                    return false;

                record.pop();
            }
        }

        return record.empty();
    }
};