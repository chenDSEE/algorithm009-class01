/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/* reverse */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        ListNode *check = head;
        vector<int> answer;
        while (check) {
            answer.push_back(check->val);
            check = check->next;
        }

        reverse(answer.begin(), answer.end());
        return answer;
    }
};


/* recusion */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> answer;
        helper(answer, head);
        return answer;
    }

    void helper(vector<int> &answer, ListNode *node) {
        if (!node)
            return ;
        
        helper(answer, node->next);
        answer.push_back(node->val);
    }
};

/* stack */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        stack<int> data_stack;
        ListNode *node = head;
        while (node) {
            data_stack.push(node->val);
            node = node->next;

        }   //  end of while

        vector<int> answer;
        while (!data_stack.empty()) {
            answer.push_back(data_stack.top());
            data_stack.pop();

        }   // end of while

        return answer;
    }
};
