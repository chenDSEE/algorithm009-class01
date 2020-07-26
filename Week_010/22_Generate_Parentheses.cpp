/* DFS - Recusion_Version */
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> answer;
        helper(answer, "", 0, 0, n);
        return answer;
    }

    void helper(vector<string> &answer, string tmp, int left, int right, const int n) {
        if (tmp.size() >= 2 * n) {
            answer.emplace_back(tmp);
            return ;
        }

        if (left < n) {
            helper(answer, tmp + '(', left + 1, right, n);
        }
        if (right < left) {
            helper(answer, tmp + ')', left, right + 1, n);
        }
    }
};

/* DFS - Non_Recusion_Version */
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        stack<pair<string, int>> wait_stack; // inter_srting -> left_count
        vector<string> answer;
        
        if (n >= 0)
            wait_stack.push({"", 0});
        
        while (!wait_stack.empty()) {
            string curr_str = wait_stack.top().first;
            int left = wait_stack.top().second;
            int right = curr_str.size() - left;
            wait_stack.pop();

            if (curr_str.size() >= 2 * n) {
                answer.emplace_back(curr_str);
                continue;
            }

            if (left < n)
                wait_stack.push({curr_str + '(', left + 1});
            if (right < n && right < left)  
                // right < n 这一点其实通过跨层的 right < left 来实现了
                // 你每一层的 one.size() < left 这点是必然的
                wait_stack.push({curr_str + ')', left});

        } // end of while

        return answer;
    }
};

/* BFS */
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        queue<pair<string, int>> wait_queue;    // inter_string -- left_cnt
        vector<string> answer;

        wait_queue.push({"", 0});
        while (!wait_queue.empty()) {
            string curr = wait_queue.front().first;
            int left = wait_queue.front().second;
            int right = curr.size() - left;
            wait_queue.pop();

            if (curr.size() >= 2 * n) {
                answer.emplace_back(curr);

            } 
            if (left < n) {
                wait_queue.push({curr + '(', left + 1});
            }
            if (right < n && right < left) {
                wait_queue.push({curr + ')', left});
            }
        }   // end of while

        return answer;
    }
};

// BFS pointer version
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        queue<pair<int, string>> wait_queue;    // left_num -> inter_status
        vector<string> answer;

        if (n >= 0)
            wait_queue.push(make_pair(0, ""));

        while (!wait_queue.empty()) {
            int left_cnt = wait_queue.front().first;
            string *one = &(wait_queue.front().second);
            int right_cnt = one->size() - left_cnt;

            if (one->size() == 2 * n) {
                answer.emplace_back(*one);

            } else {
                if (left_cnt < n)
                    wait_queue.push(make_pair(left_cnt + 1, *one + "("));
                if (right_cnt < left_cnt)
                    wait_queue.push(make_pair(left_cnt, *one + ")"));
            }

            wait_queue.pop();
        }   // end of while

        return answer;
    }
};
