/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * preorder travel ==> 知道当前节点应当填什么值，分割出新的 inorder，别忘了加偏移量
 * inorder travel  ==> 知道整棵树的整体布局（所以拿来做终止条件），子树的数量（分割新的 preorder，别忘了加偏移量）
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        init_inorder_index_map(inorder);
        return buildTree_split(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

    TreeNode* buildTree_split(const vector<int> &preorder, int pre_left_pos, int pre_right_pos, 
                              const vector<int> &inorder,  int in_left_pos,  int in_right_pos)
    {
        // term
        if (in_left_pos > in_right_pos)
            return nullptr;

        // process
        TreeNode *root = new TreeNode(preorder[pre_left_pos]);
        int in_mid_pos = index_map[root->val];
        int in_left_subtree_num = in_mid_pos - in_left_pos;

        // drill 
        root->left = buildTree_split(preorder, pre_left_pos + 1, pre_left_pos + in_left_subtree_num, 
                                     inorder, in_left_pos, in_mid_pos - 1);

        root->right = buildTree_split(preorder, pre_left_pos + in_left_subtree_num + 1, pre_right_pos, 
                                      inorder, in_mid_pos + 1, in_right_pos);

        return root;
    }

private:
    unordered_map<int, int> index_map;  // val -> index

    void init_inorder_index_map(vector<int>& inorder) {
        for (int index = 0; index < inorder.size(); index++) {
            index_map[inorder[index]] = index;
        }
    }
};

/* better version */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        init_inorder_index_map(inorder);
        return buildTree_split(preorder, 0, inorder, 0, inorder.size() - 1);
    }

    TreeNode* buildTree_split(const vector<int> &preorder, int pre_start, 
                              const vector<int> &inorder,  int in_left_pos,  int in_right_pos)
    {
        // term
        if (in_left_pos > in_right_pos)
            return nullptr;

        // process
        TreeNode *root = new TreeNode(preorder[pre_start]);
        int in_mid_pos = index_map[root->val];
        int in_left_subtree_num = in_mid_pos - in_left_pos;

        // drill 
        root->left = buildTree_split(preorder, pre_start + 1,
                                     inorder, in_left_pos, in_mid_pos - 1);

        root->right = buildTree_split(preorder, pre_start + in_left_subtree_num + 1,
                                      inorder, in_mid_pos + 1, in_right_pos);

        return root;
    }

private:
    unordered_map<int, int> index_map;  // val -> index

    void init_inorder_index_map(vector<int>& inorder) {
        for (int index = 0; index < inorder.size(); index++) {
            index_map[inorder[index]] = index;
        }
    }
};
