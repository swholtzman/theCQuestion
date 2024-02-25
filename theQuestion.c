#include <stdio.h>
#include <stdlib.h>

int INITIAL_VALUES = 0;
int NEW_ARRAY_LENGTH = 0;

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

/**
 * @brief   Reads integer values from a file and stores them in an array.
 *
 * This function reads integer values from the specified input file and dynamically
 * allocates memory to store them in an array. It returns the pointer to the array.
 *
 * @param   inputFileName   The name of the input file to be read.
 * @param   arr             Pointer to the array where values will be stored.
 * @return  int*            Pointer to the dynamically allocated array.
 *
 * @note    Exits the program with an error message if the file cannot be opened.
 */
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

/**
 * @brief   Reverses the initial linked list iteratively.
 *
 * This function reverses the initial linked list by iteratively rearranging the pointers
 * of each node. It starts from the head of the list and progresses until the end, updating
 * pointers as it goes along to reverse the order of the nodes.
 *
 * @param   head    Pointer to the head of the initial linked list.
 * @return  struct InitialNodes*    Pointer to the head of the reversed linked list.
 */
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

/**
 * @brief   Creates a linked list from an array of values.
 *
 * This function takes an array of integer values and creates a linked list from them.
 * It returns the pointer to the head of the created linked list.
 *
 * @param   arr     Array of integer values.
 * @param   size    Size of the array.
 * @return  struct InitialNodes*    Pointer to the head of the linked list.
 */
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

/**
 * @brief   Removes duplicate values from the initial linked list.
 *
 * This function removes duplicate values from the initial linked list and returns
 * the pointer to the head of the modified list.
 *
 * @param   head    Pointer to the head of the initial linked list.
 * @return  struct InitialNodes*    Pointer to the head of the modified linked list.
 */
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

/**
 * @brief   Prints the values of the initial linked list to a file.
 *
 * This function prints the values of the initial linked list to the specified output file.
 *
 * @param   outputFileName  The name of the output file.
 * @param   head            Pointer to the head of the initial linked list.
 *
 * @note    Exits the program with an error message if the file cannot be opened.
 */
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

/**
 * @brief   Adds a new node with a given value to the initial linked list.
 *
 * This function adds a new node with the specified value to the end of the initial linked list.
 * If the list is empty, it creates a new list with the new node.
 *
 * @param   head        Pointer to the head of the initial linked list.
 * @param   inputValue  The value to be added to the linked list.
 * @return  struct InitialNodes*    Pointer to the head of the modified linked list.
 *
 * @note    Exits the program with an error message if memory allocation fails.
 */
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

/**
 * @brief   Inserts a new node with a given value at a specified index in the initial linked list.
 *
 * This function inserts a new node with the specified value at the specified index in the initial linked list.
 *
 * @param   head    Pointer to the head of the initial linked list.
 * @param   val     The value to be inserted into the linked list.
 * @param   index   The index at which the new node is to be inserted.
 * @return  struct InitialNodes*    Pointer to the head of the modified linked list.
 *
 * @note    Exits the program with an error message if memory allocation fails.
 */
struct InitialNodes *insertNode(struct InitialNodes *head, int val, int index)
{
    struct InitialNodes *currentNode = head;
    struct InitialNodes *previousNode = NULL;

    // traverse list until reaching the desired
    // index or the end of the list
    int currentIndex = 0;
    while (currentNode != NULL && currentIndex < index)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
        currentIndex++;
    }

    // check if index is out of bounds
    if (currentIndex != index)
    {
        printf("Index out of bounds");
        return head;
    }

    // create a new node
    struct InitialNodes *newNode = malloc(sizeof(struct InitialNodes));
    if (newNode == NULL)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    newNode->value = val;

    // insert new node into the list
    if (previousNode == NULL)
    {
        newNode->next = head;
        head = newNode;

        // insert into middle or end of list
    }
    else
    {
        newNode->next = currentNode;
        previousNode->next = newNode;
    }

    return head;
}

struct InitialNodes *reverseIterative(struct InitialNodes *head)
{
    struct InitialNodes *prev = NULL;
    struct InitialNodes *nextNode = NULL;

    if (head == NULL)
    {
        return NULL;
    }

    while (head != NULL)
    {
        nextNode = head->next;
        head->next = prev;
        prev = head;
        head = nextNode;
    }

    head = prev;
    return head;
}

int *newArrayList(struct InitialNodes *head)
{
    if (head == NULL)
    {
        return NULL;
    }

    struct InitialNodes *runningNode = head;
    size_t size = 0;

    while (runningNode != NULL)
    {
        size++;
        runningNode = runningNode->next;
    }

    int *newArray = malloc(size * sizeof(int));
    if (newArray == NULL)
    {
        return NULL;
    }

    size_t index = 0;
    runningNode = head;
    while (runningNode != NULL)
    {
        newArray[index++] = runningNode->value;
        runningNode = runningNode->next;
    }

    NEW_ARRAY_LENGTH = size;
    return newArray;
}

int *arrayCopier(int *arr)
{
    if (arr == NULL)
    {
        return NULL;
    }

    int *copiedArray = malloc(NEW_ARRAY_LENGTH * sizeof(int));
    if (copiedArray == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < NEW_ARRAY_LENGTH; i++)
    {
        copiedArray[i] = arr[i];
    }

    return copiedArray;
}

// int *arrayReversal(int *arr)
// {
//     if (arr == NULL)
//     {
//         return NULL;
//     }

//     int *reversedArray = malloc(NEW_ARRAY_LENGTH * sizeof(int));
//     if (reversedArray == NULL)
//     {
//         return NULL;
//     }

//     size_t index = 0;
//     for (int i = NEW_ARRAY_LENGTH - 1; i >= 0; i--)
//     {
//         reversedArray[index] = arr[i];
//         index++;
//     }

//     return reversedArray;
// }

void freeList(struct InitialNodes *head)
{
    struct InitialNodes *current = head;
    while (current != NULL)
    {
        struct InitialNodes *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief   Main function of the program.
 *
 * This function serves as the entry point of the program. It orchestrates the execution
 * of various tasks such as reading values from a file, manipulating linked lists, and printing
 * results to files.
 *
 * @param   argc    Number of command-line arguments.
 * @param   argv    Array of command-line arguments.
 * @return  int     Program exit status.
 */
int main(int argc, char *argv[])
{
    const char *inputFile = argv[1];

    int *newArray = NULL;

    newArray = readValueFile(inputFile, newArray);

    // task 1
    struct InitialNodes *firstList = newNodeList(newArray, INITIAL_VALUES);

    // task 2
    struct InitialNodes *cleanedList = removeCopies(firstList);

    // task 3
    const char *outputFile = "initialList.txt";
    printInitialsToFile(outputFile, cleanedList);

    // task 4
    printf("Please enter an integer value to be added: ");
    int newVal;
    if (scanf("%d", &newVal) != 1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    cleanedList = addNode(cleanedList, newVal);

    // task 5
    printf("Please enter an integer value to be inserted: ");
    int insertValue;
    if (scanf("%d", &insertValue) != 1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    printf("Please enter an index to insert at: ");
    int index;
    if (scanf("%d", &index) != 1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    cleanedList = insertNode(cleanedList, insertValue, index);

    // task 6
    const char *addFile = "addedList.txt";
    printInitialsToFile(addFile, cleanedList);

    // Create a copy of the cleanedList
    struct InitialNodes *copyOfCleanedList = NULL;
    struct InitialNodes *temp = cleanedList;
    while (temp != NULL)
    {
        copyOfCleanedList = addNode(copyOfCleanedList, temp->value);
        temp = temp->next;
    }

    // Free the memory allocated for the cleanedList
    freeList(cleanedList);

    // task 7
    struct InitialNodes *reversedList = reverseIterative(copyOfCleanedList);
    const char *reverseFile = "firstReversedList.txt";
    printInitialsToFile(reverseFile, reversedList);

    // Free the memory allocated for the copyOfCleanedList
    freeList(copyOfCleanedList);

    // task 8
    int *intArray = newArrayList(reversedList);

    freeList(reversedList);

    // int *copiedArray = arrayCopier(intArray);
    // int i = 0;
    // while (i < NEW_ARRAY_LENGTH)
    // {
    //     printf("%d\n", copiedArray[i]);
    //     i++;
    // }

    // free(intArray);

    // int *reversedIntArray = arrayReversal(copiedArray);
    // while (i < NEW_ARRAY_LENGTH)
    // {
    //     printf("%d\n", reversedIntArray[i]);
    //     i++;
    // }


    printf("success");
    return 0;
}

// to run:
// gcc -o program theQuestion.c
// ./program