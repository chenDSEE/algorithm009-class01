class Trie {
public:
    bool  is_end;
    Trie *next[26];

    Trie() : is_end(false) {
        memset(next, 0, sizeof(next));
    }

    void insert(string word) {
        Trie *node = this;
        for (char c : word) {
            if (node->next[c - 'a'] == nullptr)
                node->next[c - 'a'] = new Trie;

            node = node->next[c - 'a'];
        }

        node->is_end = true;
    }

};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> answer;

        // create and init Trie
        Trie *root = new Trie;
        for (string w : words) {
            root->insert(w);
        }

        // search in each board[x][y]
        for (int x = 0; x < board.size(); x++) {
            for (int y = 0; y < board[x].size(); y++) {
                search_word(board, answer, "", root, x, y);
            }
        }

        return answer;
    }

    void search_word(vector<vector<char>> &board, vector<string> &answer, string curr, Trie *node, int x, int y)
    {
        if (node->is_end == true) {
            answer.emplace_back(curr);
            node->is_end = false;
            return ;
        }

        // check safty and had_traveled
        if (x < 0 || x >= board.size() || y < 0 || y >= board[x].size() || board[x][y] == '#')
            return ;

        char tmp = board[x][y];
        // only pass next Trie's node to new level of search. No need to check prefix from root to curr's end!(save time)
        // OR when board is very large, you will have to check from root for so many time unnecessary
        node = node->next[tmp - 'a']; 
        if (node == nullptr)    // check prefix
            return ;
        

        curr += tmp;
        board[x][y] = '#';
        for (int step = 0; step < 4; step++) {
            search_word(board, answer, curr, node, x + move_x[step], y + move_y[step]);
        }
        board[x][y] = tmp;
    }
private:
    int move_x[4] = {1, -1, 0, 0};
    int move_y[4] = {0,  0, 1, -1};
};


// better version
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Trie
{
public:
    bool isEnd;
    Trie *nxt[26];
    string word;
    Trie()
    {
        isEnd = 0;
        for (int i = 0; i < 26; i++)
        {
            nxt[i] = nullptr;
        }
        word = "";
    }

    void insert(string word)
    {
        Trie *node = this;
        for (char each : word)
        {
            if (node->nxt[each - 'a'] == nullptr)
            {
                node->nxt[each - 'a'] = new Trie();
            }
            node = node->nxt[each - 'a'];
        }
        node->isEnd = 1;
        node->word = word;
    }
};
class Solution
{
public:
    vector<string> ans;
    void dfs(Trie *now, int x, int y, vector<vector<char>> &board)
    {
        if (now->isEnd)
        {
            now->isEnd = 0;
            ans.push_back(now->word);
            return;
        }
        if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size())
            return;
        if (board[x][y] == '#')
            return;
        if (now->nxt[board[x][y] - 'a'] == nullptr)
            return;
        now = now->nxt[board[x][y] - 'a'];
        char cur = board[x][y];
        board[x][y] = '#';
        dfs(now, x + 1, y, board);
        dfs(now, x - 1, y, board);
        dfs(now, x, y + 1, board);
        dfs(now, x, y - 1, board);
        board[x][y] = cur;
    }
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        Trie *root = new Trie();
        for (auto word : words)
        {
            root->insert(word);
        }
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                dfs(root, i, j, board);
            }
        }
        return ans;
    }
};
