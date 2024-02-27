#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int value;
    struct ListNode *next;
};

struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode* current = head;
    struct ListNode* prev = head;

    while(current != NULL) {
        if (head -> value == val) {
            head = head -> next;
            current = head;
        } else {
            if (current -> value != val) {
                prev = current;
                current = current -> next;
            } else {
                prev -> next  = current -> next;
                current = current -> next;
            }
        }
    }

    return head;
}