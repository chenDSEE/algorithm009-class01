/* BFD */
// 即使是这种情况，你也是要避免环路的！因为你是可以反复横跳的！
// 但是，new_gen 只能是中间基因的其中一个，同时，中间基因一旦出现过一次，就没有必要出现第二次了
// 所以 gen_base 同时充当了 visited_set 的角色
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> gen_base(bank.begin(), bank.end());
        queue<pair<string, int>> wait_queue;    // new_gen -> change_count

        wait_queue.push({start, 0});

        while (!wait_queue.empty()) {
            string curr_gen = wait_queue.front().first;
            int curr_cnt = wait_queue.front().second;
            wait_queue.pop();

            for (int pos = 0; pos < curr_gen.size(); pos++) {
                string tmp = curr_gen;

                for (char change_one : "ACGT") {
                    if (curr_gen[pos] == change_one)
                        continue;
                    
                    curr_gen[pos] = change_one;
                    if (gen_base.count(curr_gen)) {
                        wait_queue.push({curr_gen, curr_cnt + 1});
                        gen_base.erase(curr_gen);   // 剪枝、避免环路
                        if (curr_gen == end)
                            return curr_cnt + 1;
                    }
                }

                curr_gen = tmp;
            }
        }   // end of while

        return -1;
    }
};

/* another version of BFS */
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        queue<string> toVisit;
        unordered_set<string> dict(bank.begin(), bank.end());
        int dist = 0;
        
        if(!dict.count(end)) return -1;
        
        toVisit.push(start);
        while(!toVisit.empty()) {
            int n = toVisit.size();
            for(int i=0; i<n; i++) {
                string str = toVisit.front();
                toVisit.pop();
                if(str==end) return dist;
                addWord(str, dict, toVisit);
            }
            dist++;
        }
        return -1;
        
    }
    
    void addWord(string word, unordered_set<string>& dict, queue<string>& toVisit) {
        dict.erase(word);
        for(int i=0; i<word.size(); i++) {
            char tmp = word[i];
            for(char c : string("ACGT")) {
                word[i] = c;
                if(dict.count(word)) {
                    toVisit.push(word);
                    dict.erase(word);
                }
            }
            word[i] = tmp;
        }
    }
};