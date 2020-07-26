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
        unordered_set<string> base(bank.begin(), bank.end());
        queue<string> wait_queue;

        if (base.count(end) == 0) {
            return -1;
        }


        int step = 0;
        wait_queue.push(start);
        while (!wait_queue.empty()) {
            int size = wait_queue.size();

            for (int cnt = 0; cnt < size; cnt++) {
                string curr = wait_queue.front();
                wait_queue.pop();

                for (int index = 0; index < curr.size(); index++) {    // for each char in this word
                    char tmp = curr[index];

                    for (char one : "ACGT") {
                        if (one != tmp) {
                            curr[index] = one;

                            if (base.count(curr) == 1) {
                                base.erase(curr);
                                wait_queue.push(curr);

                                if (curr == end) {
                                    return step + 1;
                                }
                            }
                        }
                    }

                    curr[index] = tmp;  // for next char
                }
            }

            step++;
        }

        return -1;
    }
};

/* two-ended BFS */
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> base(bank.begin(), bank.end());
        unordered_set<string> start_set, end_set;

        if (base.count(end) == 0)
            return -1;

        start_set.insert(start);
        end_set.insert(end);
        int step = 0;
        unordered_set<string> *work_set, *check_set;
        while (!start_set.empty() && !end_set.empty()) {
            if (start_set.size() > end_set.size()) {
                work_set = &end_set;
                check_set = &start_set;

            } else {
                work_set = &start_set;
                check_set = &end_set;
            }

            unordered_set<string> next_set;
            for (auto it = work_set->begin(); it != work_set->end(); it++) {
                string curr = *it;
                for (int index = 0; index < curr.size(); index++) {
                    char tmp = curr[index];

                    for (char change : "ACGT") {
                        if (change == tmp)
                            continue;

                        curr[index] = change;
                        if (check_set->count(curr) == 1)
                            return step + 1;

                        if (base.count(curr) == 1) {
                            base.erase(curr);
                            next_set.insert(curr);                        
                        }
                    }

                    curr[index] = tmp;
                }
            }

            step++;
            work_set->swap(next_set);

        }   // end of while

        return -1;
    }
};