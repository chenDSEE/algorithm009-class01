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
 * 这个跟最大深度是不一样的！你仔细看深度的定义，[1] = 1, [1,2,null,3] = 3 ! 这两个 case 很坑的！
 * 由于 [1,2,null,3] 的 最小深度是 3，所以不能跟 最大深度相似，要下一个节点有效，才能去进行 min 比较
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root)
            return 0;
        
        int right = minDepth(root->right);
        int left = minDepth(root->left);

        if (!root->left || !root->right)
            return left + right + 1;
        
        return std::min(right, left) + 1;
    }
};

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root)
            return 0;

        if (!root->left || !root->right)
            return minDepth(root->left) + minDepth(root->right) + 1;
        
        return min(minDepth(root->left) + 1, minDepth(root->right) + 1);
    }
};