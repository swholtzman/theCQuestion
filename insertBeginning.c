#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int value;
    struct ListNode *next;
};

void insertBeginning(struct ListNode** head, int value) {
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    newNode -> value = value;
    newNode -> next = *head;
    *head = newNode;
}

int main() {
    struct ListNode* head = NULL;
    insertBeginning(&head, 10);
    return 0;
}