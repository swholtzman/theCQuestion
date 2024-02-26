#include <stdio.h>
#include <stdlib.h>

int ARRAY_SIZE = 0;

struct ListNode {
    int val;
    struct ListNode* next;
};

int *toArray(struct ListNode *head, int *arr) {
    if (head == NULL) {
        return NULL;
    }

    arr = malloc(sizeof(int));
    if (arr == NULL) {
        return NULL;
    }

    size_t size = 0;
    while (head != NULL) {
        arr = realloc(arr, (size + 1) * sizeof(int));
        if (arr == NULL) {
            return NULL;
        }

        arr[size] = head -> val;
        head = head -> next;
        size++;
    }

    ARRAY_SIZE = size;
    return arr;
}


void sortArray(int *arr, int size) {
    if (arr == NULL) {
        return NULL;
    }

    quickSort(arr, 0, size - 1);
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int *recursiveBinary(int* arr, int low, int high, int target) {
    if (arr == NULL) {
        return NULL;
    }

    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            return recursiveBinary(arr, low, mid - 1, target);
        } else {
            return recursiveBinary(arr, mid + 1, high, target);
        }
    }

    return -1;
}