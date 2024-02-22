#include <stdio.h>
#include <stdlib.h>

int INITIAL_VALUES = 0;
int NEW_VALUES = 0;

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
 * @brief   Generates a new node for the initial linked list.
 *
 * This function dynamically allocates memory for a new node of the initial linked list
 * and initializes its value and next pointer.
 *
 * @param   value   The value to be stored in the new node.
 * @return  struct InitialNodes*    Pointer to the newly created node.
 *
 * @note    Exits the program with an error message if memory allocation fails.
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
    while (currentNode != NULL && currentIndex < index) {
        previousNode = currentNode;
        currentNode = currentNode -> next;
        currentIndex++;
    }

    // check if index is out of bounds
    if (currentIndex != index) {
        printf("Index out of bounds");
        return head;
    }

    // create a new node 
    struct InitialNodes *newNode = malloc(sizeof(struct InitialNodes));
    if (newNode == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    newNode -> value = val;

    // insert new node into the list
    if (previousNode == NULL) {
        newNode -> next = head;
        head = newNode;

    // insert into middle or end of list
    } else {
        newNode -> next = currentNode;
        previousNode -> next = newNode;
    }

    INITIAL_VALUES++;

    return head;

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
struct InitialNodes *reverseIterative(struct InitialNodes *head) {
    struct InitialNodes *prev = NULL;
    struct InitialNodes *nextNode = NULL;

    if (head == NULL) {
        return NULL;
    }

    while (head != NULL) {
        nextNode = head -> next;
        head -> next = prev;
        prev = head;
        head = nextNode;
    }

    head = prev;
    return head;
}




/**
 * @brief   Converts a linked list of integers to an array.
 *
 * This function traverses the linked list of integers and copies the values into
 * a dynamically allocated array.
 *
 * @param   head    Pointer to the head of the linked list.
 * @return  int*    Pointer to the array containing the values.
 */
int* nodesToArray(struct InitialNodes *head) {
    
    if (head == NULL) {
        perror("Error");
        return NULL;
    }

    int *arr = malloc(NEW_VALUES * sizeof(int));
    if (arr == NULL) {
        perror("Error");
        return NULL;
    }


    while (head != NULL) {
        
        arr[NEW_VALUES] = head -> value;
        head = head -> next;
        NEW_VALUES++;
    }

    return arr;
}




/**
 * @brief   Copies an integer array.
 *
 * This function creates a copy of the given integer array dynamically, resizing it
 * as needed to fit all elements. It returns a pointer to the newly created copy.
 *
 * @param   arr Pointer to the integer array to be copied.
 * @return  int* Pointer to the copy of the integer array.
 *              Returns NULL if the input array is NULL or memory allocation fails.
 */
int *copyIntArray(int *arr) {

    if (arr == NULL) {
        return NULL;
    }

    int *newArray = malloc(NEW_VALUES * sizeof(int));
    for (int i = 0; i < NEW_VALUES; i++) {
        newArray[i] = arr[i];
    }

    return newArray;
}



/**
 * @brief   Reverses an integer array.
 *
 * This function creates a new array that contains the elements of the input array
 * in reverse order.
 *
 * @param   arr Pointer to the integer array to be reversed.
 * @return  int* Pointer to the reversed integer array.
 *              Returns NULL if either the input array or the reversed array cannot be allocated.
 */
int *reverseArray(int *arr) {
    
    if (arr == NULL) {
        return NULL;
    }

    int *reversedArray = malloc(NEW_VALUES * sizeof(int));
    if (reversedArray == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = NEW_VALUES; i >= 0; i--) {
        reversedArray[index] = arr[i];
        index++;
    }

    return reversedArray;
}




/**
 * @brief   Prints two integer arrays to a file.
 *
 * This function prints the elements of two integer arrays to a file, separated by a newline.
 *
 * @param   outputFileName  The name of the file to write the arrays to.
 * @param   arr1            Pointer to the first integer array.
 * @param   arr2            Pointer to the second integer array.
 * @return  void
 */
void printArraysToFile(const char* outputFileName, int *arr1, int *arr2) {

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL || arr1 == NULL || arr2 == NULL) {
        return;
    }

    for (int i = 0; i < NEW_VALUES; i++) {
        fprintf(outputFile, "%d ", arr1[i]);  // Print elements of arr1 to file
    }
    fprintf(outputFile, "\n");

    for (int i = 0; i < NEW_VALUES; i++) {
        fprintf(outputFile, "%d ", arr2[i]);  // Print elements of arr2 to file
    }

    fclose(outputFile);  // Close the file after writing
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



    //task 3
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



//     // task 6
//     const char *addFile = "addedList.txt";
//     printInitialsToFile(addFile, cleanedList);



//     // task 7
//     struct InitialNodes *reversedList = reverseIterative(cleanedList);

//     // we no longer need cleanedList
//     // free(cleanedList);



//     // task 8
//     const char *reverseFile = "firstReversedList.txt";
//     printInitialsToFile(reverseFile, reversedList);



//     // task 9
//     int *intArray = nodesToArray(reversedList);

//     // we no longer need reversedList
//     free(reversedList);



//     // task 10
//     int *copiedArray = copyIntArray(intArray);


//     // we no longer need intArray
//     free(intArray);



//     // task 11
//     int *reversedArray = reverseArray(copiedArray);



//     // task 12
//     // const char *arrayForwardBackward = "arrayForwardBackward.txt"; 
//     // printArraysToFile(arrayForwardBackward, copiedArray, reversedArray);

//     return 0;

//      // to run:
//     // gcc -o program theQuestion.c
//     // ./program
}