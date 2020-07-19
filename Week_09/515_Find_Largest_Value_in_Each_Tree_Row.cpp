/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/* My BFS version */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        queue<pair<TreeNode *, int>> wait_queue;    // node -- level
        vector<int> answer;

        if (root)
            wait_queue.push({root, 0});

        while (!wait_queue.empty()) {
            TreeNode *curr_node = wait_queue.front().first;
            int curr_level = wait_queue.front().second;
            wait_queue.pop();

            if (answer.size() <= curr_level)    // pay attention for this line !
                answer.push_back(INT_MIN);

            if (curr_node->val > answer[curr_level])
                answer[curr_level] = curr_node->val;

            if (curr_node->left)
                wait_queue.push({curr_node->left, curr_level + 1});
            if (curr_node->right)
                wait_queue.push({curr_node->right, curr_level + 1});

        }   // end of while

        return answer;
    }
};

/* another BFS version */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        queue<TreeNode *> wait_queue;
        vector<int> answer;

        if (root != nullptr) {
            wait_queue.push(root);
        }

        while (!wait_queue.empty()) {
            int size = wait_queue.size();
            int max = INT_MIN;

            for (int cnt = 0; cnt < size; cnt++) {
                TreeNode *node = wait_queue.front();
                wait_queue.pop();

                max = max < node->val ? node->val : max;

                if (node->left) {
                    wait_queue.push(node->left);
                }

                if (node->right) {
                    wait_queue.push(node->right);
                }
            }
            
            answer.emplace_back(max);
        }   // end of while

        return answer;
    }
};