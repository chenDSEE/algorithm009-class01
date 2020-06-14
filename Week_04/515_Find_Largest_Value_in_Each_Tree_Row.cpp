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
        vector<int> answer;

        queue<TreeNode*> wait_queue;
        if (root)
            wait_queue.push(root);

        while(!wait_queue.empty()) {
            int levelSize = wait_queue.size();	// this line
            int levelMax = INT_MIN;
            for(int i = 0; i < levelSize; i++) {	
                TreeNode* curNode = wait_queue.front(); // and this line, 这两行实现了，知道单层 queue 有多少的需要进行遍历，更好的控制了进入 wait_queue 跟离开的情况，使过程更为可控
                wait_queue.pop();
                levelMax = max(curNode->val, levelMax);

                if(curNode->left) 
                    wait_queue.push(curNode->left);
                if(curNode->right) 
                    wait_queue.push(curNode->right);
            }
            answer.push_back(levelMax);
        }
        return answer;
    }
};