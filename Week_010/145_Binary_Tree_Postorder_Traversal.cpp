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
 * 你仔细过一遍 遍历 的核心思想！
 * 三个节点的顺序，以及什么时候输出 value，永远都只是在 root 的时候输出
 *
 * 这样你才能将所有的问题抽离出 重复的子问题
 * 不然你会发现，现在的 root->left 就是下一次的 root，所以你要合理的抽离出 重复的子问题，只在一个情况下输出值，
 * 在这两种情况下进行值输出，会出事的！
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> answer;
        travel_tree(answer, root);
        return answer;
    }

    void travel_tree(vector<int> &answer, TreeNode *root) {
        if (root != NULL) {
            travel_tree(answer, root->left);    // root 的子节点永远都是在不断向下探索，只有当 root 节点的时候，才会输出值
            travel_tree(answer, root->right);
            answer.push_back(root->val);    // 注意：你会发现，永远只有在自己是 root 节点的时候，才会进行值输出
        }
    }
};



/**
 * nullptr 仅仅只是作为一个标志：下一个 栈帧 是需要进行 值输出 的栈帧；没有 nullptr 的就是需要继续进行 deeper 探索的栈帧
 * 所以，你也可以把 flag 打在每一个栈帧旁边。
 * 
 * 你仔细看会发现，nullptr 是打在 curr 后面的！为什么？
 * 因为在递归算法中，只有 当前的 root 节点会进行值输出，这是对于 重复子问题 的抽离！
 *
 * 而入栈顺序，正好就是递归的入栈顺序，所以能够保证值输出的顺序正确
 *
 *
 *
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode *> node_stack;
        vector<int> answer;

        if (root) {
            node_stack.push(root);
        }

        TreeNode *curr = nullptr;   // use nullptr to dientify "next node is curr_node in recusion"
        while (!node_stack.empty()) {
            curr = node_stack.top();
            node_stack.pop();
            if (curr != nullptr) { // this node need search deeper
                node_stack.push(curr);
                node_stack.push(nullptr);   // when you come across this nullptr, you can know that ""NEXT node is curr_node in recusion""
                if (curr->right) {
                    node_stack.push(curr->right);
                }
                if (curr->left) {
                    node_stack.push(curr->left);
                }

            } else {    // this node's value is one of answer
                answer.push_back(node_stack.top()->val);
                node_stack.pop();   // get this node's value, pop it
            }

        }   // end of while

        return answer;
    }
};


/**
 * 反转 answer 进行遍历，何等恐怖。具体解释看 590 的题解
 */

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode *> node_stack;
        vector<int> answer;

        if (root)
            node_stack.push(root);

        TreeNode *curr = nullptr;
        while (!node_stack.empty()) {
            curr = node_stack.top();
            node_stack.pop();
            answer.push_back(curr->val);
            if (curr->left)
                node_stack.push(curr->left);
            if (curr->right)
                node_stack.push(curr->right);

        }   // end of while

        reverse(answer.begin(), answer.end());
        return answer;
    }
};