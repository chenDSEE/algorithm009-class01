/**
 * 高效的暴力，是 sort 之后直接进行对比 ！而不是你傻傻的一个个字母去检查
*/
class Solution {
public:
    bool isAnagram(string s, string t) {
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());
        return s == t;
    }
};

/**
 * 我们需要两个计数器数表进行比较吗？实际上不是，因为我们可以用一个计数器表计算 ss 字母的频率，
 * 用 tt 减少计数器表中的每个字母的计数器，然后检查计数器是否回到零。
 * 
 * 注意，这里事得到了最前面的 if (s.size() != t.size()) 的约束才会有这么好看的方式，s 负责加、t 负责减。
 * 不同字母肯定不为零；
 * 字母数量不同的话，由于 长度相等的关系，也是不会为 0 的
*/
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size())
            return false;

        int hash_array[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            hash_array[s[i] - 'a']++;
            hash_array[t[i] - 'a']--;
        }

        for (int i : hash_array) {
            if (i != 0)
                return false;
        }

        return true;
    }
};

/**
 * 这个，节省一点点时间的。这是一边减，一边检验，上面的是计数完毕之后，再来检验
 * 
 * 我们可以先用计数器表计算 ss，然后用 tt 减少计数器表中的每个字母的计数器。
 * 如果在任何时候计数器低于零，我们知道 tt 包含一个不在 ss 中的额外字母，并立即返回 FALSE。
*/
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size())
            return false;

        int hash_table[26] = {0};
        for (char c : s) {
            hash_table[c - 'a']++;
        }
        for (char c : t) {
            hash_table[c - 'a']--;
            if (hash_table[c - 'a'] < 0) {
                return false;
            }
        }

        return true;
    }
};