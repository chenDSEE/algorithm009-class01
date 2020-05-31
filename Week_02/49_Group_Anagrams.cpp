/**
 * 这时候跟以前就不一样了，key 不再是单个 字母，而是一个 字符串，所以你得用 STL 提供的 map 了。
 * 以 sort 之后的 字符串 作为 key，然后对应一个 vector （因为这样你才能够装得下多个可能备选输出啊） 
 * 
 * 剩下的其实就是一些基本操作了。重点还是在于：你能不能够将具体问题抽象成为相应的数据结构
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> answer;
        unordered_map<string, vector<string>> string_map;

        for (string check : strs) {
            string tmp = check;
            std::sort(tmp.begin(), tmp.end());
            string_map[tmp].push_back(check);
        }

        for (auto check : string_map) {
            answer.push_back(check.second);
        }

        return answer;
    }
};

/**
 * 上面的为什么要进行两次循环？
 * 因为我没有办法通过 sort 之后的字符串，得知这个字符串对应 vector<string> answer 的具体哪一个坑位啊
 * 所以才会把字符串作为 map 的 value,一股脑的往 作为 value 的 vector 里面塞
 * 
 * 看看下面的额优化版本，value 是 index，这样就可以省去一个小小的循环了
*/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> answer;
        unordered_map<string, int> index_map;  // key - index

        int index = 0;
        for (string &check : strs) {  // pass by reference ! speed up
            string tmp = check;
            std::sort(tmp.begin(), tmp.end());

            if (index_map.count(tmp)) {
                answer[index_map[tmp]].push_back(check);

            } else {
                index_map[tmp] = index++;
                answer.push_back(vector<string> {check});   // answer[index_map[tmp]] is not init, therefor you should push a vecotor into back, but not use "answer[index_map[tmp]].push_back(check)"
            }
        }

        return answer;
    }
};