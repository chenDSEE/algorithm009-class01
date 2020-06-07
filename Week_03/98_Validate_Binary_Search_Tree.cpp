/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 由于 BST 中，每一个父节点都会导致子节点的范围改变，所以你最好是把更新后的范围进去！
// 另外，树的最小子问题理应是：某一个节点！而不是 一个父节点 + 两个子节点 ！
// 之前的递归也好，什么都好，为什么一次递归只输出一次值？因为最小的子问题是 一个节点！
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MAX, LONG_MIN);
    }

    bool helper(TreeNode *root, long max, long min) {
        if (!root) {
            return true;
        }
        if (root->val >= max)
            return false;
        if (root->val <= min)
            return false;
        if (!helper(root->left, root->val, min))
            return false;
        if (!helper(root->right, max, root->val))
            return false;

        return true;
    }
};

/* better version */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, NULL, NULL);
    }

    bool helper(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
        if(!root) 
            return true;
        
        if (minNode && root->val <= minNode->val)
            return false;
        if (maxNode && root->val >= maxNode->val)
            return false;
        if (!helper(root->left, minNode, root))
            return false;
        if (!helper(root->right, root, maxNode))
            return false;
        
        return true;
    }
};



class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long last_val = LONG_MIN;
        return helper(root, last_val);
    }

    bool helper(TreeNode* root, long &last_val) {
        if(!root) 
            return true;
        
        if (!helper(root->left, last_val))
            return false;
        
        if (root->val <= last_val)
            return false;
        last_val = root->val;
        
        if (!helper(root->right, last_val))
            return false;

        return true;
    }
};