#include <stdio.h>
#include <stdlib.h>

int INITIAL_VALUES = 0;

struct InitialNodes
{
    int value;
    struct InitialNodes *next;
};

struct LaterNodes
{
    int value;
    struct LaterNodes *next;
};

int *readValueFile(const char *inputFileName, int *arr)
{
    FILE *inputFile = fopen(inputFileName, "r");

    if (inputFile == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    size_t size = 0;
    int value;
    while (fscanf(inputFile, "%d", &value) == 1)
    {

        arr = realloc(arr, (size + 1) * sizeof(int));

        if (arr == NULL)
        {
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

struct InitialNodes *generateNode(int value)
{
    struct InitialNodes *newNode = malloc(sizeof(struct InitialNodes));

    if (newNode == NULL)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

struct InitialNodes *newNodeList(int arr[], int size)
{
    struct InitialNodes *head = NULL;
    struct InitialNodes *tail = NULL;

    for (int i = 0; i < size; i++)
    {
        struct InitialNodes *newNode = generateNode(arr[i]);

        // first node
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;

            // remainder of the list
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

struct InitialNodes *removeCopies(struct InitialNodes *head)
{
    struct InitialNodes *current = head;

    // iterate through the full list with current holding a position
    while (current != NULL && current->next != NULL)
    {
        struct InitialNodes *runner = current;

        // runner will "run" through the full length of the
        // list until there are no more values
        while (runner->next != NULL)
        {

            // if the value stored at current is equal to the value stored at the runner
            if (current->value == runner->next->value)
            {

                // initiate a node to equal that which we know to be a duplicate
                struct InitialNodes *trashCollector = runner->next;

                // allow the runner to point to the node beyond
                // that which it is currently pointing
                runner->next = runner->next->next;

                // delete the duplicate node
                free(trashCollector);
            }
            else
            {
                // move the runner to whatever its pointing at
                runner = runner->next;
            }
        }
        // current moves one forward
        current = current->next;
    }
    return head;
}

void printInitialsToFile(const char *outputFileName, struct InitialNodes *head)
{
    FILE *outputFile = fopen(outputFileName, "w");

    if (outputFile == NULL)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    struct InitialNodes *printingNode = head;

    int printNum;

    while (printingNode != NULL)
    {
        printNum = printingNode->value;
        fprintf(outputFile, "%d\n", printNum);
        printingNode = printingNode->next;
    }

    fclose(outputFile);
}

struct InitialNodes *addNode(struct InitialNodes *head, int inputValue)
{
    struct InitialNodes *newNode = malloc(sizeof(struct InitialNodes));

    if (newNode == NULL)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    newNode->value = inputValue;

    // list is empty
    if (head == NULL)
    {
        head = newNode;
        newNode->next = NULL;
    }
    else
    {

        // find the last node of the list
        struct InitialNodes *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }

        // add new node to the end of the list
        current->next = newNode;
        newNode->next = NULL;
    }

    return head;
}

struct InitialNodes *insertNode(struct InitialNodes *head, int val, int index)
{
    
}

int main(int argc, char *argv[])
{
    // to run:
    // gcc -o program theQuestion.c
    // ./program

    const char *inputFile = "values1.txt";

    int *newArray = NULL;

    newArray = readValueFile(inputFile, newArray);

    // task 1
    struct InitialNodes *firstList = newNodeList(newArray, INITIAL_VALUES);

    // we have our node list, we dont need the array anymore
    free(newArray);

    // task 2
    struct InitialNodes *cleanedList = removeCopies(firstList);

    // we have our new list, we can free the old one
    free(firstList);

    const char *outputFile = "initialList.txt";
    printInitialsToFile(outputFile, cleanedList);

    printf("Please enter an integer value to be added: ");
    int newVal;
    if (scanf("%d", &newVal) != 1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    addNode(cleanedList, newVal);

    const char *outputFile2 = "finalList.txt";
    printInitialsToFile(outputFile2, cleanedList);

    printf("success");
    return 0;
}