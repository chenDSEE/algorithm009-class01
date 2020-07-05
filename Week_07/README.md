# Two - Ended BFS 模板

```c++
/* two-ended BFS */
/* 双向 BFS */
// 重点：从左右两边同时开始搜索，相遇即得到答案（所有，return 前是看看自己当前满足变化要求的中间结果，
//       是不是能在对面的 visited 里面找到，是的话那就是结果）
//
// A_wait_queue.size() <  B_wait_queue.size() ???
// 之所以要这样做判断，其实是 双向 BFS 诞生的原因
// BFS 面临的问题是：随着搜索的深入，每一轮的可能子结果增多，宽度变得太大了，所以每次检查的时候，我们都是去
// 检查宽度比较小的哪一个 queue，这样才是真正满足 双向 BFS 加速的核心方法。
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end()), A_visit, B_visit;
        if (dict.count(endWord) == 0)
            return 0;
        
        queue<string> A_wait_queue, B_wait_queue;
        A_wait_queue.push(beginWord);
        B_wait_queue.push(endWord);
        A_visit.insert(beginWord);
        B_visit.insert(endWord);

        int step = 1;
        while (!A_wait_queue.empty() && !B_wait_queue.empty()) {
            /* 选择宽度小的 queue 进行 BFS */
            queue<string> *A_queue_p = A_wait_queue.size() <  B_wait_queue.size() ? &A_wait_queue : &B_wait_queue; 
            unordered_set<string> *A_viste_p = A_wait_queue.size() <  B_wait_queue.size() ? &A_visit : &B_visit; 
            queue<string> *B_queue_p = A_wait_queue.size() >= B_wait_queue.size() ? &A_wait_queue : &B_wait_queue; 
            unordered_set<string> *B_viste_p = A_wait_queue.size() >= B_wait_queue.size() ? &A_visit : &B_visit; 

            int size = A_queue_p->size();
            for (int cnt = 0; cnt < size; cnt++) {  // 本层 BFS
                string curr_str = A_queue_p->front();
                A_queue_p->pop();

                for (int index = 0; index < curr_str.size(); index++) {
                    char tmp = curr_str[index];

                    for (char one = 'a'; one <= 'z'; one++) {
                        if (one == curr_str[index])
                            continue;

                        curr_str[index] = one;
                        
                        if (B_viste_p->count(curr_str) == 1)    // 相遇，找到了
                            return step + 1;    

                        if (dict.count(curr_str) == 1) {
                            A_queue_p->push(curr_str);
                            A_viste_p->insert(curr_str);
                            dict.erase(curr_str);
                        }

                    }

                    curr_str[index] = tmp;
                }
            }
            step++;

        }   // end of while

        return 0;
    }
};
```









# 单词搜索 II 时间复杂度分析

```c++
typedef struct Trie_s Trie_t;

typedef struct Trie_s {
    bool is_end;
    Trie_t *next[26];
} Trie_t;

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie_t *root = new Trie_t;
        memset(root->next, 0, sizeof(root->next)); 
        root->is_end = false;
        
        // create Trie(O(words.size() * each_word.size()))
        for (string w : words) {
            Trie_t *node = root;
            for (char c : w) {
                if (node->next[c - 'a'] == nullptr) {
                    node->next[c - 'a'] = new Trie_t;
                    memset(node->next[c - 'a'], 0, sizeof(Trie_t)); 
                    node->next[c - 'a']->is_end = false;
                }

                node = node->next[c - 'a'];
            }
            node->is_end = true;
        }

        // DFS search for each_start_point in board
        // O(board.size() * board[0].size())
        vector<string> answer;
        for (int x = 0; x < board.size(); x++) {
            for (int y = 0; y < board[x].size(); y++) {
                DFS_search(board, root, "", x, y, answer);
            }
        }

        return answer;
    }

private:
    

    void DFS_search(vector<vector<char>>& board, Trie_t *node, string curr_str, 
                    int x, int y, vector<string> &answer)
    {
        if (node->is_end == true) {
            answer.emplace_back(curr_str);
            node->is_end = false;
            return ;
        }
        
        if (x < 0 || x >= board.size() || y < 0 || y >= board[x].size()
            || board[x][y] == '#')
        {
            return ;
        }

        char tmp = board[x][y];
        node = node->next[tmp - 'a'];
        if (node == nullptr)
            return ;

        curr_str += tmp;

        board[x][y] = '#';
        // for 4 possible move
        DFS_search(board, node, curr_str, x + 1, y, answer);
        DFS_search(board, node, curr_str, x - 1, y, answer);
        DFS_search(board, node, curr_str, x, y + 1, answer);
        DFS_search(board, node, curr_str, x, y - 1, answer);
        board[x][y] = tmp;
    }

};
```



1. create Trie(O(words.size() * each_word.size()));
2. DFS search for each_start_point in board: O(board.size() * board[0].size())
   1. 4 possible move : O(4)



Totally: O(words.size() * each_word.size() + board.size() * board[0].size() * 4)