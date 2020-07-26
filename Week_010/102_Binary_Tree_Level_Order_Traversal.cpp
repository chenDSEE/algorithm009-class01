/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/* DFS - Recusion_version */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> answer;
        DFS_travel_tree(answer, root, 0);
        return answer;
    }

    void DFS_travel_tree(vector<vector<int>> &answer, TreeNode *root, int level) {
        if (root) {
            if (answer.size() < level + 1)
                answer.push_back(vector<int> {});

            answer[level].push_back(root->val);
            DFS_travel_tree(answer, root->left, level + 1);
            DFS_travel_tree(answer, root->right, level + 1);
        }
    }
};

/* DFS - Iteration */




/* BFS */
// 既然 queue 里面装的都是排队等待被访问的节点，那你在把节点往 queue 里面填装之前就要自己确认一下究竟是否为空
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> answer;
        queue<TreeNode *> search_queue;

        if (root)
            search_queue.push(root);

        while (!search_queue.empty()) {
            int cnt = search_queue.size();
            answer.emplace_back(vector<int> ());

            for (int i = 0; i < cnt; i++) {
                TreeNode *curr = search_queue.front();
                search_queue.pop();
                answer.back().emplace_back(curr->val);
                
                if (curr->left)
                    search_queue.push(curr->left);
                if (curr->right)
                    search_queue.push(curr->right);
            }     
        }   // end of while

        return answer;
    }
};


