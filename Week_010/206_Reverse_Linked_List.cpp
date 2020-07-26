/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = NULL;
        ListNode *next = head;

        while (head != NULL) {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        } // end of while (head != NULL)

        head = prev;
        return head;
    }
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;

        ListNode *last_one = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;

        /* this will be new head !; this is the last_one_node, you will find that this never been change !
         * just pass out from head->next == NULL !
         */
        return last_one;
    }
};