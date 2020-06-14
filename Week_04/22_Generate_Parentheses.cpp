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