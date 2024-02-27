#include <stdio.h>
#include <stdlib.h>



struct ListNode
{
    int value;
    struct ListNode *next;
};

struct ListNode* oddEvenList(struct ListNode *head) {
    if (head == NULL) {
        return NULL;
    }

    struct ListNode* odd = head;
    struct ListNode* even = head -> next;
    struct ListNode* evenStart = even;

    while(odd -> next && even -> next) {
        odd -> next = odd -> next -> next;
        odd = odd -> next;
        even -> next = even -> next -> next;
        even = even -> next;
    }

    odd -> next = evenStart;
    return head;
}