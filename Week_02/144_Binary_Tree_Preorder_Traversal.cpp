/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> answer;
        travel_tree(answer, root);
        return answer;
    }

    void travel_tree(vector<int> &answer, TreeNode *root) {
        if (root != NULL) {
            answer.push_back(root->val);
            travel_tree(answer, root->left);
            travel_tree(answer, root->right);
        }
    }
};



class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode *> recusion_stack;
        vector<int> answer;

        TreeNode *curr = root;
        while (curr != NULL || !recusion_stack.empty()) {
            while (curr != NULL) {
                answer.push_back(curr->val);
                recusion_stack.push(curr);
                curr = curr->left;
            }

            curr = recusion_stack.top();
            recusion_stack.pop();

            curr = curr->right;
        }

        return answer;
    }
};