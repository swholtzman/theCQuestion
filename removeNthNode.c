#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int value;
    struct ListNode *next;
};

struct ListNode *removeNthNode(struct ListNode* head, int n) {
    struct ListNode *start = malloc(sizeof(struct ListNode));
    start -> next = head;
    struct ListNode *current = start;
    struct ListNode *delay = start;

    for (int i = 0; i < n; i++) {
        current = current -> next;
    }

    while ((current -> next) != NULL) {
        delay = delay -> next;
        current = current -> next;
    }

    delay -> next = delay -> next -> next;

    return start -> next;
}