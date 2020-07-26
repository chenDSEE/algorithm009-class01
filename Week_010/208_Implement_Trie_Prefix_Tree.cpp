class Trie {
private:
    /** 我们可以看到TrieNode结点中并没有直接保存字符值的数据成员，那它是怎么保存字符的呢？
     * next 字母映射表的 index 实际上就是暗含了 下一个节点究竟是什么字母
     * 
     * 之所以不用 next[index] = NULL 来标识 end，是因为，你没有办法区分这两种情况：
     * 1. 一个字符串的结束；
     * 2. next[index] 这个坑并没有被使用
     *
     * NOTE: 只要能够匹配到第一个字符，那这个分支的最末尾必然是 isEnd = true 的
     */
    bool isEnd;      // 该结点是否是一个串的结束
    Trie* next[26];  //字母映射表
public:
    Trie() {
        isEnd = false;
        memset(next, 0, sizeof(next));
    }
    
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            if (node->next[c-'a'] == NULL) {
                node->next[c-'a'] = new Trie();
            }
            node = node->next[c-'a'];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            node = node->next[c - 'a'];
            if (node == NULL) {
                return false;
            }
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        Trie* node = this;
        for (char c : prefix) {
            node = node->next[c-'a'];   // 先这么做的好处在于：node 指向的就是你要检查的那个函数指针，做少一次 curr - 'a' 的操作
            if (node == NULL) {
                return false;
            }
        }
        return true;
    }
};

// my version
class Trie {

private:
    bool  is_end;
    Trie *next[26];

public:
    /** Initialize your data structure here. */
    Trie() : is_end(false) {
        memset(next, 0, sizeof(next));
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie *node = this;

        // insert every char for word
        for (char curr : word) {
            if (node->next[curr - 'a'] == nullptr) {
                node->next[curr - 'a'] = new Trie;
            }
            node = node->next[curr - 'a'];
        }

        // mark end of branch
        node->is_end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie *node = this;

        for (char curr : word) {
            if (node->next[curr - 'a'] == nullptr)
                return false;
            
            node = node->next[curr - 'a'];
        }

        return node->is_end;    // 这里是要求完全匹配，最后面的自然是要 is_end = true
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie *node = this;

        for (char curr : prefix) {
            if (node->next[curr - 'a'] == nullptr)
                return false;
            
            node = node->next[curr - 'a'];
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */