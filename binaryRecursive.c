#include <stdio.h>
#include <stdlib.h>

int FILE_SIZE = 0;

struct Node
{
    int value;
    struct Node *next;
};

int *readFile(int *arr, const char *inputFileName)
{
    FILE *inputFile = fopen(inputFileName, "r");

    if (inputFile == NULL)
    {
        return NULL;
    }

    size_t size = 0;
    int val;
    while (fscanf(inputFile, "%d", &val) == 1)
    {
        arr = realloc(arr, (size + 1) * sizeof(int));

        if (arr == NULL)
        {
            return NULL;
        }

        arr[size] = val;
        size++;
    }

    FILE_SIZE = size;

    return arr;
}

int *sortArray(int *arr, int length)
{
    if (arr == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < length; i++)
    {
        for (int j = i; j < length; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

    return arr;
}

// RECURSIVE MERGE SORT
// O(nlog(n))

void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // create temporary arrays
    int leftArray[n1], rightArray[n2];

    // copy data to temporary arrays leftArray[] and rightArray[]
    for (i = 0; i < n1; i++)
    {
        leftArray[i] = arr[left + i];
    }

    for (j = 0; j < n2; j++)
    {
        rightArray[j] = arr[mid + 1 + j];
    }

    // merge temporary arrays back into arr[left...right]
    i = 0;    // initial index of first subarray
    j = 0;    // initital index of second subarray
    k = left; // initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (leftArray[i] <= rightArray[j])
        {
            arr[k] = leftArray[i];
            i++;
        }
        else
        {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // copy remaining elements of leftArray[], if there are any
    while (i < n1)
    {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // copy remaining elements of rightArray[], if there are any
    while (j < n2)
    {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {

        // sam as (left + right) / 2 but avoids overflow
        // for large left and right
        int mid = left + (right - left) / 2;

        // sort first and second halves of arr
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // merge the two sorted halves
        merge(arr, left, mid, right);
    }
}
// END OF RECURSIVE MERGE SORT BLOCK

int recursiveBinary(int *arr, int target, int low, int high)
{

    if (high >= low)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] > target)
        {
            return recursiveBinary(arr, target, low, mid - 1);
        }

        return recursiveBinary(arr, target, mid + 1, high);
    }

    // number not found
    return -1;
}

struct Node *createNode(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

struct Node *arrayToNodes(int *arr, int length, struct Node *head)
{
    struct Node *tail = NULL;

    if (arr == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < length; i++) {

        struct Node *newNode = createNode(arr[i]);

        if (newNode == NULL) {
            return NULL;
        }

        // if its the first Node in the list
        if (head == NULL) {
            head = newNode;
            tail = newNode;

        // for the rest of them
        } else {
            tail -> next = newNode;
            tail = newNode;
        } 
    }

    return head;
}

struct Node *reverseList(struct Node *head) {
    if (head == NULL) {
        return NULL;
    }

    struct Node *temp = NULL;
    struct Node *prev = NULL;

    while (head != NULL) {
        temp = head -> next;
        head -> next = prev;
        prev = head;
        head = temp;
    }

    head = prev;

    return head;
}

int main(int argc, char *argv[])
{
    int *arr = NULL;

    const char *inputFile = argv[1];

    arr = readFile(arr, inputFile);

    int arr_size = FILE_SIZE;

    printf("Given array is \n");
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    mergeSort(arr, 0, arr_size - 1);

    printf("Sorted array is \n");
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int searchNumber = 0;
    printf("What number would you like to find? ");
    scanf("%d", &searchNumber);

    int result = recursiveBinary(arr, searchNumber, 0, arr_size - 1);
    result >= 0 ? printf("Your number was at index: %d\n", result) : printf("Your number is not in the array");


    struct Node *nodeArray = NULL;
    nodeArray = arrayToNodes(arr, arr_size, nodeArray);

    nodeArray = reverseList(nodeArray);

    struct Node *currentNode = nodeArray;
    while (currentNode != NULL) {
        printf("%d\n", currentNode -> value);
        currentNode = currentNode -> next;
    }
}