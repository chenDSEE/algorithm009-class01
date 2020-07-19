class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());

        if (dict.count(endWord) == 0)
            return 0;

        queue<pair<string, int>> wait_queue;   // interim_string -> cnt
        unordered_set<string> visited;
        wait_queue.push({beginWord, 1});
        visited.insert(beginWord);

        while (!wait_queue.empty()) {
            string curr = wait_queue.front().first;
            int cnt = wait_queue.front().second;
            if (curr == endWord)
                return cnt;
                
            wait_queue.pop();

            for (int index = 0; index < curr.size(); index++) {
                string tmp = curr;
                for (char one : "qazxswedcvfrtgbnhyujmkiopl") {
                    if (curr[index] != one) {
                        curr[index] = one;
                        if (dict.count(curr) != 0 && visited.count(curr) == 0) {
                            wait_queue.push({curr, cnt + 1});
                            visited.insert(curr);
                        }
                        curr = tmp;
                    }    
                }
            }
        }

        return 0;
    }
};

// better version
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());

        if (dict.count(endWord) == 0)
            return 0;

        queue<pair<string, int>> wait_queue;   // interim_string -> cnt
        wait_queue.push({beginWord, 1});

        while (!wait_queue.empty()) {
            string curr = wait_queue.front().first;
            int cnt = wait_queue.front().second;
            if (curr == endWord)
                return cnt;
                
            wait_queue.pop();

            for (int index = 0; index < curr.size(); index++) {
                string tmp = curr;
                for (char one : "qazxswedcvfrtgbnhyujmkiopl") {
                    if (curr[index] != one) {
                        curr[index] = one;
                        if (dict.count(curr) != 0) {
                            wait_queue.push({curr, cnt + 1});
                            dict.erase(curr);   // 避免使用 visited ！
                        }
                        curr = tmp;
                    }    
                }
            }
        }

        return 0;
    }
};

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

// better version
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end()), A_record, B_record;
        if (dict.count(endWord) == 0)
            return 0;
        
        A_record.insert(beginWord);
        B_record.insert(endWord);

        int step = 1;
        unordered_set<string> *work_set, *check_set;
        while (!A_record.empty() && !B_record.empty()) {
            if (A_record.size() < B_record.size()) {
                work_set = &A_record;
                check_set = &B_record;

            } else {
                work_set = &B_record;
                check_set = &A_record;
            }


            unordered_set<string> next_set;
            for (auto it = work_set->begin(); it != work_set->end(); it++) {
                string curr_str = *it;

                for (int index = 0; index < curr_str.size(); index++) {
                    char tmp = curr_str[index];

                    for (char one = 'a'; one <= 'z'; one++) {
                        if (one == curr_str[index])
                            continue;

                        curr_str[index] = one;
                        
                        if (check_set->count(curr_str) == 1)
                            return step + 1;    

                        if (dict.count(curr_str) == 1) {
                            next_set.insert(curr_str);
                            dict.erase(curr_str);
                        }

                    }

                    curr_str[index] = tmp;
                }
            }
            step++;
            work_set->swap(next_set);
        }   // end of while

        return 0;
    }
};

