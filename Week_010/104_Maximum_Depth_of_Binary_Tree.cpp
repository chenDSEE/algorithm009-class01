/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 104_Maximum_Depth_of_Binary_Tree
class Solution {
public:
    int maxDepth(TreeNode* root) {
        int max_level = 0;
        helper(root, max_level, 1);
        return max_level;
    }

    void helper(TreeNode *root, int &max_level, int cur_level) {
        if (root) {
            helper(root->left, max_level, cur_level + 1);
            helper(root->right, max_level, cur_level + 1);

        } else {
            if (max_level < cur_level - 1) {
                max_level = cur_level - 1;          
            }
        }
    }

};

/* better version */
// 104_Maximum_Depth_of_Binary_Tree
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root)
            return 0;

        return max(maxDepth(root->left) + 1, maxDepth(root->right) + 1);
    }
};