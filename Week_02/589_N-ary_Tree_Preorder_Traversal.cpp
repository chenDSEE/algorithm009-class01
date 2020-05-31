/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> answer;
        travel_tree(answer, root);
        
        return answer;
    }

    void travel_tree(vector<int> &answer, Node *root) {
        if (root) {
            answer.push_back(root->val);

            for (Node *check : root->children) {
                travel_tree(answer, check);
            }
        }
    }
};


/* iteratively */
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> answer;
        stack<Node *> node_stack;

        if (root)
            node_stack.push(root);

        Node *curr = nullptr;
        while (!node_stack.empty()) {
            curr = node_stack.top();
            node_stack.pop();
            if (curr) {
                for (int i = curr->children.size() - 1; i >= 0; i--) {  // pay attention for this line
                    if (curr->children[i]) {                            // pay attention for this line
                        node_stack.push(curr->children[i]);
                    }
                }
                node_stack.push(curr);
                node_stack.push(nullptr);

            } else {
                answer.push_back(node_stack.top()->val);
                node_stack.pop();
            }
        }

        return answer;
    }
};


// 也不是不行，效果一般般罢了
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> answer;
        stack<Node *> node_stack;

        if (root)
            node_stack.push(root);
        Node *curr = nullptr;
        while (!node_stack.empty()) {
            curr = node_stack.top();
            node_stack.pop();
            answer.push_back(curr->val);

            for (int i = curr->children.size() - 1; i >= 0 && curr->children[i]; i--) {
                node_stack.push(curr->children[i]);
            }
        }

        return answer;
    }
};