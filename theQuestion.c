#include <stdio.h>
#include <stdlib.h>

int INITIAL_VALUES = 0;

struct InitialNodes {
    int value;
    struct InitialNodes *next;
};

struct LaterNodes {
    int value;
    struct LaterNodes *next;
};

int *readValueFile(const char* inputFileName, int *arr) {
    FILE *inputFile = fopen(inputFileName, "r");
    
    if (inputFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    size_t size = 0;
    int value;
    while (fscanf(inputFile, "%d", &value) == 1) {


        arr = realloc(arr, (size + 1) * sizeof(int));

        if (arr == NULL) {
            perror("Error");
            exit(EXIT_FAILURE);
        }

        arr[size] = value;
        INITIAL_VALUES++;
        size++;
    }

    fclose(inputFile);

    return arr;
}

struct InitialNodes *generateNode(int value) {
    struct InitialNodes *newNode = malloc(sizeof(struct InitialNodes));
    if (newNode == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    newNode -> value = value;
    newNode -> next = NULL;

    return newNode;
}

struct InitialNodes *newNodeList(int arr[], int size) {
    struct InitialNodes *head = NULL;
    struct InitialNodes *tail = NULL;

    for (int i = 0; i < size; i++) {
        struct InitialNodes *newNode = generateNode(arr[i]);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail -> next = newNode;
            tail = newNode;
        }
    }

    return head;
}

struct InitialNodes *removeCopies(struct InitialNodes *head) {
    struct InitialNodes *nextNode = NULL;
    struct InitialNodes *lastNode = NULL;

    while(head -> next != NULL) {
        
    }
}

int main(int argc, char *argv[]) {
    // to run:
    // gcc -o program theQuestion.c 
    // ./program

    const char *inputFile = "values1.txt";

    int *newArray = NULL;

    newArray = readValueFile(inputFile, newArray);

    // task 1
    struct InitialNodes *firstList = newNodeList(newArray, INITIAL_VALUES);

    printf("Node Contents\n");
    while (firstList != NULL) {
        printf("%d\n", firstList -> value);
        firstList = firstList -> next;
    }

    printf("success");
    return 0;
}