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
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> answer;
        travel_tree(answer, root, 0);
        return answer;
    }

    void travel_tree(vector<vector<int>> &answer, const Node *root, int level) {
        if (root) {
            if (answer.size() < level + 1) 
                answer.push_back(vector<int> {});

            answer[level].push_back(root->val);
            for (Node *check : root->children) {
                travel_tree(answer, check, level + 1);
            }
        }
    }
};

// BFS Version
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> answer;
        
        // BFS
        queue<Node *> wait_queue;
        if (root != nullptr) {
            wait_queue.push(root);
        }

        while (!wait_queue.empty()) {
            int size = wait_queue.size();
            vector<int> one;
            for (int cnt = 0; cnt < size; cnt++) {
                Node *curr = wait_queue.front();
                wait_queue.pop();

                one.emplace_back(curr->val);
                for (auto child : curr->children) {
                    wait_queue.push(child);
                }
            }

            answer.emplace_back(one);
        }

        return answer;
    }
};