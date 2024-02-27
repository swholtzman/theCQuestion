#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* swapPairs(struct ListNode* head) {
    if (head == NULL || head -> next == NULL) {
        return head;
    }

    struct ListNode *dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy -> next = head;
    struct ListNode *prev = dummy;

    while (prev -> next && prev -> next -> next) {
        struct ListNode* first = prev -> next;
        struct ListNode* second = first -> next;

        // swapping
        first -> next = second -> next;
        second -> next = first;
        prev -> next = second; 

        // next pair
        prev = first;
    }

    struct ListNode* newHead = dummy -> next;
    free(dummy);
    return newHead;
}