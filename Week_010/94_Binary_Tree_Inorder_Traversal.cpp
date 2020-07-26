/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// recursion solution
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> answer;
        travel_tree(answer, root);
        return answer;
    }

    void travel_tree(vector<int> &answer, TreeNode *root) {
        if (root != NULL) {
            travel_tree(answer, root->left);
            answer.push_back(root->val);
            travel_tree(answer, root->right);
        }
    }

};

// using stack to analog recursion
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> answer;
        stack<TreeNode *> recusion_stack;

        TreeNode *curr_node = root;
        /**
         * 1. curr 为 NULL，但是 stack 不为空，则这个右节点时 空 的，但会上一层 stack
         * 2. 只有当 stack 为空（没有上一层可以返回），且新的节点（一般是上一次循环的右节点）为空，待会结束循环

         * cure_node != NULL 是为了进行右节点尽头的判断
         * stack empty 才是真正的模拟栈实现
        */
        // 寻找右节点的尽头，同时寻找 stack 为 NULL 的时机
        while (curr_node != NULL || !recusion_stack.empty()) {  // iff 当前节点为 NULL 且 stack 为空时， 推出循环
            while (curr_node != NULL) { // 左节点的尽头，这是在寻找左节点的尽头
                recusion_stack.push(curr_node);
                curr_node = curr_node->left;
            }

            curr_node = recusion_stack.top();   // 返回上一层栈帧
            recusion_stack.pop();

            answer.push_back(curr_node->val);   // 输出中序的 中间值
            curr_node = curr_node->right;       //将右节点当作中间节点，准备去找她的左节点
        }
    
        return answer;
    }

};
// 有空看看这个https://leetcode-cn.com/problems/binary-tree-inorder-traversal/solution/yan-se-biao-ji-fa-yi-chong-tong-yong-qie-jian-ming/


class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode *> recusion_stack;
        vector<int> answer;

        // 既然是我们进行压栈，那么在压栈前检查要压入的栈帧是否有效是更好的行为，甚至是必须的，因为你用 nullptr 作为 flag 了
        // 所以确保这个 flag 不被乱用是你必须做的事情
        if (root)   
            recusion_stack.push(root);

        while (!recusion_stack.empty()) {
            TreeNode *node = recusion_stack.top();
            recusion_stack.pop();
            if (node != nullptr) {  // 注意压栈的顺序问题
                if (node->right)
                    recusion_stack.push(node->right);

                recusion_stack.push(node);
                recusion_stack.push(nullptr);   // 这个就可以保证 当 node == nullptr 的时候，recusion.top() 一定存在

                if (node->left)
                    recusion_stack.push(node->left);

            } else {
                answer.push_back(recusion_stack.top()->val);
                recusion_stack.pop();
            }

        }
        return answer;
    }
};