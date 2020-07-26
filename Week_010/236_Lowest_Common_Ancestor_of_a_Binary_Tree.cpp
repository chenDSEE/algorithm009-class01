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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root)
            return NULL;

        if (root ==  p || root == q)
            return root;

        TreeNode *left  = lowestCommonAncestor(root->left , p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        if (!left)
            return right;   // right == NULL   and   right != NULL
        if (!right)
            return left;    // left == NULL   and   left != NULL

        if (left && right)
            return root;    // I'm lowest Common Ancestor, just return ME, not master which level
        
        return NULL;
    }
};

// better to understand
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root)
            return NULL;

        if (root ==  p || root == q)
            return root;

        TreeNode *left  = lowestCommonAncestor(root->left , p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        if(left && right)
            return root;
        else
            return left ? left : right;
    }
};



/**
 * 终止条件：找到了 p\q 返回自己，自己是 NULL，则返回不存在（有多少不可分割的逻辑，就有多少不可复用的代码）
 * 子问题：看看自己是不是公共祖先，是的话返回自己；不是的话，则返回左/右子树找到的 p\q\NULL\p+q
 * 当自己是公共祖先节点的时候返回自己，且上面那几层都会是直接返回这个公共节点
 * （因为每一个下探，返回的都是：自己认为自己所找到的公共节点位置。没有就是返回 NULL，说明自己没有找到）
 * 这里就很巧妙了，毕竟找到公共节点的上一层并不知道这一件事！仅仅只是把可能的答案往上传递罢了
 * （毕竟题目确保了 p\q 一定存在，所以不用标记都找到了，直接返回可能的答案就好）
 */

/**
 * If the current (sub)tree contains both p and q, then the function result is their LCA. 
 * If only one of them is in that subtree, then the result is that one of them. 
 * If neither are in that subtree, the result is null/None/nil.
 */
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) 
        return root;

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    return !left ? right : (!right ? left : root);
}

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q)
            return root;

        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        if (left != nullptr && right != nullptr)
            return root;

        return left != nullptr ? left : right;
    }
};