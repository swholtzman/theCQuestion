#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int value;
    struct ListNode *next;
};





// RELEVANT CODE BEGINS
void sortedInsert(struct ListNode** headRef, struct ListNode *newNode) {
    struct ListNode *current;
    if (*headRef == NULL || (*headRef) -> value >= newNode -> value) {
        newNode -> next = *headRef;
        *headRef = newNode;
    } else {
        current = *headRef; 
        while (current -> next != NULL && current -> next -> value < newNode -> value) {
            current = current -> next;
        }

        newNode -> next = current -> next;
        current -> next = newNode;
    }
}

void insertSort(struct ListNode **headRef) {
    struct ListNode *sorted = NULL;
    struct ListNode *current = *headRef;
    struct ListNode *next;
    while (current != NULL) {
        next = current -> next;
        sortedInsert(&sorted, current);
        current = next;
    }
    *headRef = sorted;
}
// RELEVANT CODE ENDS










// helper function to add nodes to the list head
void push(struct ListNode **headRef, int newValue) {
    struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (newNode == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    newNode -> value = newValue;
    newNode -> next = *headRef;
    *headRef = newNode;

}

void printList(struct ListNode *head) {
    while (head != NULL) {
        printf("%d ->", head -> value);
        head = head -> next;
    }   
        printf("NULL\n");
}

int main() {
    struct ListNode *head = NULL;
    push(&head, 6);
    push(&head, 3);
    push(&head, 7);
    push(&head, 9);
    push(&head, 4);
    push(&head, 1);
    push(&head, 2);
    push(&head, 10);
    push(&head, 8);
    push(&head, 5);

    printf("Original List: \n");
    printList(head);

    insertSort(&head);

    printf("Sorted List: \n");
    printList(head);

    return 0;
}




