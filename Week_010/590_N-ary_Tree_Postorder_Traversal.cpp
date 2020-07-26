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
    vector<int> postorder(Node* root) {
        vector<int> answer;
        travel_tree(answer, root);
        return answer;
    }

    void travel_tree(vector<int> &answer, Node *root) {
        if (root) {
            for (Node *check : root->children) {
                travel_tree(answer, check);
            }
            answer.push_back(root->val);
        }
    }
};


/* iteratively */
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
    vector<int> postorder(Node* root) {
        vector<int> answer;
        stack<Node *> node_stack;

        if (root) {
            node_stack.push(root);
        }

        Node *curr = nullptr;
        while (!node_stack.empty()) {
            curr = node_stack.top();
            node_stack.pop();
            if (curr) {
                node_stack.push(curr);
                node_stack.push(nullptr);

                for (int i = curr->children.size() - 1; i >= 0 && curr->children[i]; i--) {
                    node_stack.push(curr->children[i]);
                }

            } else {
                answer.push_back(node_stack.top()->val);
                node_stack.pop();
            }

        }   // end of while

        return answer;
    }
};

/* 采用反转方案的遍历 */
