class Solution {
private:
    unordered_map<char, string> num_map;
public:
    vector<string> letterCombinations(string digits) {
        init_map();
        vector<string> answer;
        letterCombinations_split(digits, answer, "");
        return answer;
    }

/**
 *      map<char, string> M = {
 *          {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"},
 *          {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
 *      };
 */

    void init_map() {
        num_map['2'] = "abc";
        num_map['3'] = "def";
        num_map['4'] = "ghi";
        num_map['5'] = "jkl";
        num_map['6'] = "mno";
        num_map['7'] = "pqrs";
        num_map['8'] = "tuv";
        num_map['9'] = "wxyz";
    }

    void letterCombinations_split(const string &digits, vector<string> &answer, string tmp) {
        if (tmp.size() >= digits.size()) {
            if (tmp.size() > 0)
                answer.push_back(tmp);
                
            return ;
        }

        if (num_map.count(digits[tmp.size()]) <= 0) // check for safety
            return ;

        for (char num : num_map[digits[tmp.size()]]) {
            letterCombinations_split(digits, answer, tmp + num);
        }

        return ;
    }
};

// 恢复的方式
void backtracking(const vector<vector<char>>& table, vector<string>& res, string& local, int index, const string& digits) {
    if(index==digits.size())
        res.push_back(local);
    else
        for(int i=0;i<table[digits[index]-'0'].size();i++) {
            local.push_back(table[digits[index]-'0'][i]);   // this
            backtracking(table, res, local, index+1, digits);
            local.pop_back();                               // and this is restore
        }
}