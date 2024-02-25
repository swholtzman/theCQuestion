#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int value;
    struct ListNode *next;
};

struct ListNode *removeMiddleNode(struct ListNode *head) {
    if (head == NULL) {
        return NULL;
    }

    int length = 1;
    struct ListNode *counter = head;
    while (counter != NULL) {
        counter = counter -> next;
        length++;
    }

    int middle = (length / 2);

    struct ListNode *start = malloc(sizeof(struct ListNode));
    start -> next = head;
    struct ListNode *current = start;
    struct ListNode *delay = start;

    for (int i = 0; i < middle; i++) {
        current = current -> next;
    }

    while ((current -> next) != NULL) {
        delay = delay -> next;
        current = current -> next;
    }

    delay -> next = delay -> next -> next;
    struct ListNode *newHead = start -> next;
    free(start);
    return newHead;

}