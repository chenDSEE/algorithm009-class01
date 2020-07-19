// hash table
class Solution {
public:
    int numJewelsInStones(string J, string S) {
        unordered_set<char> is_jewel;
        for (char c : J) {
            is_jewel.insert(c);
        }

        int cnt = 0;
        for (char c : S) {
            if (is_jewel.count(c) == 1) {
                cnt++;
            }
        }

        return cnt;
    }
};